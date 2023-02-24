#include "Board.h"
#include "CSVHandler.h"

Board::Board() : printer("test", BOARD_WIDTH, BOARD_HEIGHT) {
	int i, j;

	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			this->area[i][j] = 0;
		}
	}

	this->decideTarget();
}

void Board::loadBoard(const char* fname) {
	int i, j;
	CSVFile data;
	data.csv_read(fname, false, false, ',');

	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			if (data.cell.at(i).at(j) != 0)
				this->area[i][j] = -1;
		}
	}

	this->decideTarget();
}

bool Board::putPiece(uint8_t(*fig)[FIG_WIDTH], int x, int y) {
	int fig_num, put_num;
	int i, j;
	POINT fig_t;

	put_num = 0;
	fig_num = 0;

	fig_t.x = this->target.x - x;
	fig_t.y = this->target.y - y;
	if (fig_t.x < 0 || FIG_WIDTH <= fig_t.x || fig_t.y < 0 || FIG_HEIGHT <= fig_t.y) {
		return false;
	}
	if (fig[fig_t.y][fig_t.x] == 0) {
		return false;
	}

	for (i = 0; i < FIG_HEIGHT; i++) {
		if (y + i < BOARD_HEIGHT){
			for (j = 0; j < FIG_WIDTH; j++) {
				if (x + j < BOARD_WIDTH) {
					if (fig[i][j] != 0) {
						if (this->area[y + i][x + j] == 0) {
							fig_num = fig[i][j];
							this->area[y + i][x + j] = fig_num;
							put_num += 1;
						}
					}
				}
			}
		}
	}

	if (put_num == PIECE_SIZE) {
		this->decideTarget();
		return true;
	}

	//this->deletePiece(fig_num);
	if (fig_num != 0) {
		for (i = 0; i < FIG_HEIGHT; i++) {
			if (y + i < BOARD_HEIGHT) {
				for (j = 0; j < FIG_WIDTH; j++) {
					if (x + j < BOARD_WIDTH) {
						if (this->area[y + i][x + j] == fig_num) {
							this->area[y + i][x + j] = 0;
						}
					}
				}
			}
		}
	}

	return false;
}

void Board::deletePiece(int fig_num) {
	int i, j;


	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			if (this->area[i][j] == fig_num) {
				this->area[i][j] = 0;
			}
		}
	}

	this->decideTarget();
}


uint8_t(*Board::getArea())[BOARD_WIDTH]{
	return(this->area);
}

bool Board::isFilled() {
	int i, j;

	for (i = 0; i < BOARD_HEIGHT; i++)
		for (j = 0; j < BOARD_WIDTH; j++)
			if (this->area[i][j] != 0)
				return false;

	return true;
}

uint8_t workspace[BOARD_HEIGHT][BOARD_WIDTH];
uint8_t backlog[BOARD_HEIGHT][BOARD_WIDTH];
bool Board::isFragmentation() {
	uint8_t i, j, k;
	uint8_t island_num;
	uint8_t min_v[2];
	bool loopflag;
	
	//for (i = 0; i < BOARD_HEIGHT; i++) {
	//	for (j = 0; j < BOARD_WIDTH; j++) {
	//		workspace[i][j] = 0;
	//		//backlog[i][j] = 0;
	//		if (this->area[i][j] < 127) {
	//			workspace[i][j] = this->area[i][j];
	//		}
	//	}
	//}
	island_num = 0;
	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			if (this->area[i][j] == 0) {
				min_v[0] = island_num;
				// check up
				if (i != 0 && j % 2 == 0)
					if (workspace[i - 1][j + 1] < min_v[0]) min_v[0] = workspace[i - 1][j + 1];
				// check left
				if (j != 0)
					if (workspace[i][j - 1] < min_v[0]) min_v[0] = workspace[i][j - 1];
				workspace[i][j] = min_v[0];
				island_num = min_v[0] + 1;
			}
			else {
				workspace[i][j] = 255;
			}
		}
	}

	loopflag = true;
	while (loopflag) {
		loopflag = false;
		std::memcpy(backlog, workspace, BOARD_HEIGHT * BOARD_WIDTH);
		for (k = 0; k < 2; k++) {
			for (i = 0; i < BOARD_HEIGHT; i++) {
				for (j = 1 + k * 2; j < BOARD_WIDTH; j += 4) {
					if (workspace[i][j] != 255) {
						min_v[0] = workspace[i][j];
						min_v[1] = workspace[i][j - 1];
						// check down
						if (i != BOARD_HEIGHT - 1)
							if (workspace[i + 1][j - 1] < min_v[0]) min_v[0] = workspace[i + 1][j - 1];
						// check right
						if (j != BOARD_WIDTH - 1)
							if (workspace[i][j + 1] < min_v[1]) min_v[1] = workspace[i][j + 1];
						if (min_v[0] > min_v[1]) {
							min_v[0] = min_v[1];
						}

						workspace[i][j] = min_v[0];
						if (workspace[i][j - 1] != 255)
							workspace[i][j - 1] = min_v[0];
						if (i != BOARD_HEIGHT - 1)
							if (workspace[i + 1][j - 1] != 255)
								workspace[i + 1][j - 1] = min_v[0];
						if (j != BOARD_WIDTH - 1)
							if (workspace[i][j + 1] != 255)
								workspace[i][j + 1] = min_v[0];
					}
				}
			}
		}
		loopflag = std::memcmp(backlog, workspace, BOARD_HEIGHT * BOARD_WIDTH);
	}

	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			if (workspace[i][j] != 255) {
				if (workspace[i][j] > 0) {
					// if there are two island, return;
					return true;
				}
			}
		}
	}
	// then there is only one island.
	return false;
}

bool Board::allClose(uint8_t(*board_area)[BOARD_WIDTH]) {
	return(false);
}


void Board::printBoard(int wait_time) {
	printer.print((uint8_t *)this->area, wait_time);
}

void Board::decideTarget() {
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
			if (this->area[y][x] == 0) {
				this->target.y = y;
				this->target.x = x;
				return;
			}
		}
	}
}
