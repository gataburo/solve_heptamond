#include "Piece.h"

Piece::Piece() {
	std::fill((uint8_t*)this->fig, (uint8_t *)(this->fig + FIG_HEIGHT), (uint8_t)0);
	std::fill((uint8_t*)this->modfig, (uint8_t *)(this->modfig + MODFIG_HEIGHT), (uint8_t)0);
}

void Piece::loadFig(CSVFile data, uint8_t start_iter, uint8_t fig_num){
	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int j = 0; j < FIG_WIDTH; j++) {
			if (data.cell.at(i + start_iter).at(j) != 0)
				this->fig[i][j] = fig_num;
			else
				this->fig[i][j] = 0;
		}
	}
}

void Piece::setFig(uint8_t (*fig)[FIG_WIDTH]) {
	memcpy(this->fig, fig, sizeof(this->fig));
}

bool Piece::figEqual(uint8_t(*fig)[FIG_WIDTH]) {
	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int j = 0; j < FIG_WIDTH; j++) {
			if (this->fig[i][j] != fig[i][j])
				return false;
		}
	}
	return true;
}

void Piece::rotatePiece() {
	this->initModFig();
	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int j = 0; j < FIG_WIDTH; j++) {
			int xbias = (j + 1) >> 1;
			int ybias = MODFIG_HEIGHT -1 - xbias * 2 - i * 2;
			this->modfig[i + xbias][j + ybias] = this->fig[i][j];
		}
	}

	this->copyModFigToFig();
}

void Piece::flipPiece() {
	this->initModFig();

	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int j = 0; j < FIG_WIDTH; j++) {
			int xbias = (j + 1) >> 1;
			int ybias = MODFIG_HEIGHT - 1 - j * 2;
			this->modfig[i + xbias][j + ybias] = this->fig[i][j];
		}
	}

	this->copyModFigToFig();
}

void Piece::printPiece() {

	std::cout << "-------------------------------------\n";
	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int k = 0; k < i; k++)
			std::cout << " ";
		for (int j = 0; j < FIG_WIDTH; j++) {
			if (this->fig[i][j] == 0) {
				if (j % 2 == 0)
					std::cout << "¤";
				else
					std::cout << "¢";
			}
			else {
				if (j % 2 == 0)
					std::cout << "¥";
				else
					std::cout << "£";
			}
		}
		std::cout << "\n";
	}

}

void Piece::printPiece2(uint8_t* fig) {
	std::cout << "-------------------------------------\n";
	for (int i = 0; i < FIG_HEIGHT; i++) {
		for (int k = 0; k < i; k++)
			std::cout << " ";
		for (int j = 0; j < FIG_WIDTH; j++) {

			if (*(fig + (i * FIG_WIDTH) + j) == 0) {
				if (j % 2 == 0)
					std::cout << "¤";
				else
					std::cout << "¢";
			}
			else {
				if (j % 2 == 0)
					std::cout << "¥";
				else
					std::cout << "£";
			}
		}
		std::cout << "\n";
	}

}

void Piece::initModFig() {
	std::fill((uint8_t*)this->modfig, (uint8_t*)(this->modfig + MODFIG_HEIGHT), (uint8_t)0);
}

void Piece::normalizeModFig() {
	// move most left
	while (this->sumModFig(1, 1) == 0) {
		this->chinkModFig(0, 2);
	}
	// move most up
	while (this->sumModFig(0, 0) == 0) {
		this->chinkModFig(1, 1);
	}
}

void Piece::copyModFigToFig() {
	this->normalizeModFig();

	for (int i = 0; i < FIG_HEIGHT; i++)
		for (int j = 0; j < FIG_WIDTH; j++)
			this->fig[i][j] = this->modfig[i][j];
}

/* axis == 0 then mean row sum */
/* axis == 1 then mean col sum */
int Piece::sumModFig(int axis, int index) {
	int sum = 0;
	
	if (axis == 0) {
		for (int j = 0; j < MODFIG_WIDTH; j++)
			sum += this->modfig[index][j];
	}
	else {
		for (int i = 0; i < MODFIG_HEIGHT; i++)
			sum += this->modfig[i][index];
	}

	return sum;
}

/* axis == 0 then chink left 1 col */
/* axis == 1 then chink up   1 row */
void Piece::chinkModFig(int axis, int move_val) {
	if (axis == 0) {
		for (int i = 0; i < MODFIG_HEIGHT; i++) {
			for (int j = 0; j < MODFIG_WIDTH - move_val; j++) {
				this->modfig[i][j] = this->modfig[i][j + move_val];
				this->modfig[i][j + move_val] = 0;
			}
			//for (int j = MODFIG_WIDTH - move_val; j < MODFIG_WIDTH; j++)
			//	this->modfig[i][j] = 0;
		}
	}
	else {
		for (int j = 0; j < MODFIG_WIDTH; j++) {
			for (int i = 0; i < MODFIG_HEIGHT - move_val; i++) {
				this->modfig[i][j] = this->modfig[i + move_val][j];
				this->modfig[i + move_val][j] = 0;
			}
			//for (int i = MODFIG_HEIGHT - move_val; i < MODFIG_HEIGHT; i++)
				//this->modfig[i][j] = 0;
		}
	}
}
