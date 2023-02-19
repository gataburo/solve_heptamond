#pragma once

#include <iostream>
#include "Parameter.h"
#include "Pieces.h"

class AdvPieces {
private:
	std::vector<Pieces> adv_pieces;
public:
	AdvPieces();
	void addPieces(Pieces pcs);
	Pieces getPieces(uint8_t pcs_num);
	void delPieces(uint8_t pcs_num);
	void delPiece(uint8_t pcs_num, uint8_t p_num);
	void printAdvPieces();
	int size();
	Piece* retThisPiece(uint8_t pcs_num, uint8_t p_num);

	uint8_t(*getFig(uint8_t pcs_num, uint8_t p_num))[FIG_WIDTH];
};

inline Pieces AdvPieces::getPieces(uint8_t pcs_num) {
	return this->adv_pieces[pcs_num];
}

inline int AdvPieces::size() {
	return this->adv_pieces.size();
}

