#include "Pieces.h"

Pieces::Pieces() {
	return;
}

void Pieces::loadPieces(const char* fname, uint8_t p_num) {
	Piece piece;
	CSVFile data;
	data.csv_read(fname, false, false, ',');
	
	for (int i = 0; i < PIECE_NUM; i++) {
		piece.loadFig(data, i * HRF_PIECE_SIZE, i + 1);
		this->pieces.push_back(piece);
	}
}

void Pieces::addPiece(Piece piece) {
	this->pieces.push_back(piece);
}

void Pieces::delPiece(uint8_t p_num) {
	this->pieces.erase(this->pieces.begin() + p_num);
	//this->pieces[p_num] = this->pieces.back();
	//this->pieces.pop_back();
}

void Pieces::printPieces() {
	for (int i = 0; i < this->pieces.size(); i++) {
		this->pieces[i].printPiece();
	}
}

Piece* Pieces::retThisPiece(uint8_t p_num) {
	return((this->pieces[p_num]).retThis());
}
