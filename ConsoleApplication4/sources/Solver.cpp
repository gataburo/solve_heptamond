#include "Solver.h"
#include <conio.h>
#include <filesystem>

Solver::Solver(AdvPieces* adv_pcs_pt, Board* bd_pt){
	this->adv_pcs_pt = adv_pcs_pt;
	this->bd_pt = bd_pt;
	for (int i = 0; i < PIECE_NUM; i++) {
		this->p_pos.mn[i] = 255;
		this->p_pos.x[i] = 255;
		this->p_pos.y[i] = 255;
	}
	this->readData();
	put_n = 0;
}

Solver::~Solver() {
	// ˆÓ–¡‚È‚³‚»‚¤
	this->saveData();
}

uint8_t Solver::solve() {
	return recusSolve();
}

uint8_t Solver::recusSolve() {
	uint8_t pn, mn, x, y, ret;
	uint16_t hash_v;
	ret = 0;

	if (_kbhit()) {
		std::cout << "hit\n";
		_getch();
		this->bd_pt->printBoard(1);
		saveData();
		std::cout << "saved\n";
		this->bd_pt->printBoard(0);
	}

	if (this->isAllPut()) {
		if (!this->isInclude(this->p_pos, this->answers)) {
			this->answers.push_back(this->p_pos);
			this->bd_pt->printBoard(0);
			return 1;
		}
	}
	
	for (pn = 0; pn < PIECE_NUM; pn++) {
		if(this->p_pos.mn[pn] != 255)
			continue;
		for (mn = 0; mn < this->adv_pcs_pt->getPieces(pn).size(); mn++) {
			for (y = 0; y < BOARD_HEIGHT; y++) {
				for (x = 0; x < BOARD_WIDTH; x += 2) {
					if (this->bd_pt->putPiece(this->adv_pcs_pt->getFig(pn, mn), x, y) == true) {
						this->p_pos.mn[pn] = mn;
						this->p_pos.x[pn] = x;
						this->p_pos.y[pn] = y;
						hash_v = calcHash();
						if (!this->isInclude(this->p_pos, this->tried_list[hash_v])) {
							if (!this->bd_pt->isFragmentation()) {
								this->bd_pt->printBoard(1);
								this->put_n += 1;
								ret = this->recusSolve();
								this->put_n -= 1;
							}
							this->tried_list[hash_v].push_back(this->p_pos);
						}
						this->p_pos.mn[pn] = 255;
						this->p_pos.x[pn] = 255;
						this->p_pos.y[pn] = 255;
						this->bd_pt->deletePiece(pn + 1);
					}
				}
			}
		}
	}
	
	
	return 0;
}

bool Solver::isAllPut() {
	if (put_n == PIECE_NUM)
		return true;
	else
		return false;
}

bool Solver::isInclude(PIECE_POS p_pos, std::vector<PIECE_POS> list) {
	uint8_t i;
	//int itr = 0;

	for (auto element : list) {
		if (memcmp(&p_pos, &element, 72) == 0) {
			return true;
		}
		//i = 0;
		//while (p_pos.mn[i] == element.mn[i] && p_pos.x[i] == element.x[i] && p_pos.y[i] == element.y[i]){
		//	i++;
		//	if (i == PIECE_NUM) {
		//		//std::cout << itr << ", " << list.size() << "\n";
		//		return true;
		//	}
		//}
		//itr++;
	}
	return false;
}

uint16_t Solver::calcHash() {
	uint16_t hash_v = 0;

	for (int i = 0; i < PIECE_NUM; i++) {
		hash_v += (p_pos.mn[i] + 1) * p_pos.x[i] * p_pos.y[i] * i * (PIECE_NUM - i);
	}
	hash_v = hash_v >> 3;

	return hash_v;
}

bool Solver::saveData() {
	int i;

	writeBinary(SAVE_FILE_ANS, this->answers);
	for (i = 0; i < HASH_MAX; i++) {
		if (!this->tried_list[i].empty()) {
			writeBinary(SAVE_FILE_TRY + to_string(i) + ".bin", this->tried_list[i]);
		}
	}

	return true;
}

bool Solver::readData() {
	int i;

	readBinary(SAVE_FILE_ANS, this->answers);
	for (i = 0; i < HASH_MAX; i++) {
		readBinary(SAVE_FILE_TRY + to_string(i) + ".bin", this->tried_list[i]);
	}

	return true;
}

bool Solver::writeBinary(std::string filepath, std::vector<PIECE_POS>& vec) {
	int i=0;
	std::ofstream fout(filepath, std::ios::out | std::ios::binary);
	for (const auto& element : vec) {
		fout.write((char*)&element, PIECE_NUM * 3);
	}
	fout.close();
	return true;
}

bool Solver::readBinary(std::string filepath, std::vector<PIECE_POS>& vec) {
	PIECE_POS buf;
	std::ifstream fin(filepath, std::ios::in | std::ios::binary);
	if (!fin)
		return false;
	while (!fin.eof()) {
		fin.read((char*)&buf, PIECE_NUM * 3);
		vec.push_back(buf);
	}
	fin.close();
	return true;
}
