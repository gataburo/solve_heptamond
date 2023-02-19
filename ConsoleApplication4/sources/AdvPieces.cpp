#include "AdvPieces.h"

AdvPieces::AdvPieces() {
	return;
}

void AdvPieces::addPieces(Pieces pcs) {
	this->adv_pieces.push_back(pcs);
}

void AdvPieces::delPieces(uint8_t pcs_num) {
	this->adv_pieces.erase(this->adv_pieces.begin() + pcs_num);
}

void AdvPieces::delPiece(uint8_t pcs_num, uint8_t p_num) {
	this->adv_pieces[pcs_num].delPiece(p_num);
}

void AdvPieces::printAdvPieces() {
	for (int i = 0; i < this->adv_pieces.size(); i++) {
		this->adv_pieces[i].printPieces();
	}
}

Piece* AdvPieces::retThisPiece(uint8_t pcs_num, uint8_t p_num) {
	return (this->adv_pieces[pcs_num]).retThisPiece(p_num);
}


uint8_t(*AdvPieces::getFig(uint8_t pcs_num, uint8_t p_num))[FIG_WIDTH]{
	return (this->adv_pieces[pcs_num].getPiece(p_num).getFig());
}
