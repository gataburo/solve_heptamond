#pragma once

#include <iostream>
#include "Parameter.h"
#include "Piece.h"
#include "CSVHandler.h"

class Pieces {
private:
	std::vector<Piece> pieces;
public:
	Pieces();
	void loadPieces(const char* fname, uint8_t p_num);
	void addPiece(Piece piece);
	Piece getPiece(uint8_t p_num);
	void delPiece(uint8_t p_num);
	void printPieces();
	int size();
	Pieces* retThis();
	Piece* retThisPiece(uint8_t p_num);
};

inline Piece Pieces::getPiece(uint8_t p_num) {
	return this->pieces[p_num];
}

inline int Pieces::size() {
	return this->pieces.size();
}

inline Pieces* Pieces::retThis() {
	return this;
}
