#pragma once

#include <iostream>
#include "Parameter.h"
#include "CSVHandler.h"

#define MODFIG_HEIGHT PIECE_SIZE + 1
#define MODFIG_WIDTH (HRF_PIECE_SIZE*2+1)

class Piece {
private:
	uint8_t fig[FIG_HEIGHT][FIG_WIDTH];
	uint8_t modfig[MODFIG_HEIGHT][MODFIG_WIDTH];

public:
	Piece();
	void loadFig(CSVFile data, uint8_t start_iter, uint8_t fig_num);
	void setFig(uint8_t(*fig)[FIG_WIDTH]);
	uint8_t(*getFig())[FIG_WIDTH];
	bool figEqual(uint8_t(*fig)[FIG_WIDTH]);
	void rotatePiece();
	void flipPiece();
	void printPiece();
	void printPiece2(uint8_t* fig);
	Piece* retThis();
	uint8_t* retThisFig();
private:
	void initModFig();
	void normalizeModFig();
	void copyModFigToFig();
	int sumModFig(int axis, int index);
	void chinkModFig(int axis, int move_val);
};

inline uint8_t(*Piece::getFig())[FIG_WIDTH] {
	return(this->fig);
}

inline Piece* Piece::retThis() {
	return(this);
}

inline uint8_t* Piece::retThisFig() {
	return(&(this->fig[0][0]));
}
