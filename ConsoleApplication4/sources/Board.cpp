#include "Board.h"
#include "CSVHandler.h"

Board::Board() : printer("test", BOARD_WIDTH, BOARD_HEIGHT) {
	int i, j;

	for (i = 0; i < BOARD_HEIGHT; i++) {
		for (j = 0; j < BOARD_WIDTH; j++) {
			this->area[i][j] = 0;
		}
	}
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
}

bool Board::putPiece(uint8_t(*fig)[FIG_WIDTH], int x, int y) {
	int fig_num, put_num;
	int i, j;

	put_num = 0;
	fig_num = 0;
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

bool Board::isFragmentation() {
	uint8_t i, j;
	uint8_t workspace[BOARD_HEIGHT][BOARD_WIDTH];
	//uint8_t backlog[BOARD_HEIGHT][BOARD_WIDTH];
	uint8_t island_num;
	//uint8_t max_v;
	uint8_t min_v;
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
				min_v = island_num;
				// check up
				if (i != 0 && j % 2 == 0)
					if (workspace[i - 1][j + 1] < min_v) min_v = workspace[i - 1][j + 1];
				// check left
				if (j != 0)
					if (workspace[i][j - 1] < min_v) min_v = workspace[i][j - 1];
				workspace[i][j] = min_v;
				island_num = min_v + 1;
			}
			else {
				workspace[i][j] = 255;
			}
		}
	}

	//while (!std::equal(workspace, workspace+BOARD_HEIGHT*BOARD_WIDTH, backlog)) {
	loopflag = true;
	while (loopflag) {
		loopflag = false;
		for (i = 0; i < BOARD_HEIGHT; i++) {
			for (j = 0; j < BOARD_WIDTH; j++) {
				//std::cout << std::setfill('0') << std::right << std::setw(3) << int(workspace[i][j]);
				//std::cout << " ";
				if (workspace[i][j] != 255) {
					// set log
					//backlog[i][j] = workspace[i][j];

					// find min_value in near
					min_v = workspace[i][j];
					// check up
					if (i != 0 && j % 2 == 0)
						if (workspace[i - 1][j + 1] < min_v) min_v = workspace[i - 1][j + 1];
					// check down
					if (i != BOARD_HEIGHT - 1 && j % 2 == 1)
						if (workspace[i + 1][j - 1] < min_v) min_v = workspace[i + 1][j - 1];
					// check left
					if (j != 0)
						if (workspace[i][j - 1] < min_v) min_v = workspace[i][j - 1];
					// check right
					if (j != BOARD_WIDTH - 1)
						if (workspace[i][j + 1] < min_v) min_v = workspace[i][j + 1];

					if (workspace[i][j] != min_v) {
						// set min_value in near
						workspace[i][j] = min_v;
						loopflag = true;
					}
				}
			}
			//std::cout << "\n";
		}
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

