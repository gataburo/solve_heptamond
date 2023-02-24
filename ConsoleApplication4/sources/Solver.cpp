#include "Solver.h"
#include <conio.h>
#include <filesystem>

Solver::Solver(AdvPieces* adv_pcs_pt, Board* bd_pt){
	this->adv_pcs_pt = adv_pcs_pt;
	this->bd_pt = bd_pt;
	this->readData();
}

uint8_t Solver::solve() {
	uint8_t pn, mn, x, y;
	uint8_t i;
	uint8_t mn_size;
	PIECE_POS p_pos;
	bool arl_put[PIECE_NUM];
	time_t t_init;

	t_init = time(NULL);
	for (int i = 0; i < PIECE_NUM; i++) {
		p_pos.pn[i] = 0;
		p_pos.mn[i] = 0;
		p_pos.y[i] = 0;
		p_pos.x[i] = 0;
		arl_put[i] = false;
	}
	i = 0;
	while (1) {
		for (pn = p_pos.pn[i]; pn < PIECE_NUM; pn++) {
			if (arl_put[pn])
				continue;
			mn_size = this->adv_pcs_pt->getPieces(pn).size();
			for (mn = p_pos.mn[i]; mn < mn_size; mn++) {
				for (y = p_pos.y[i]; y < BOARD_HEIGHT; y++) {
					for (x = p_pos.x[i]; x < BOARD_WIDTH; x += 2) {
						if (this->bd_pt->putPiece(this->adv_pcs_pt->getFig(pn, mn), x, y) == true) {
							if (this->bd_pt->isFragmentation()) {
								this->bd_pt->deletePiece(pn + 1);
							}
							else {
								p_pos.pn[i] = pn;
								p_pos.mn[i] = mn;
								p_pos.y[i] = y;
								p_pos.x[i] = x += 2;
								arl_put[pn] = true;
								i++;
								if (i == PIECE_NUM) {
									this->answers.push_back(p_pos);
									this->bd_pt->printBoard(1);
									std::cout << "elapsed time: " << time(NULL) - t_init << "[s], ";
									std::cout << "find answers: " << this->answers.size() << "\n";
									this->bd_pt->deletePiece(pn + 1);
									arl_put[pn] = false;
									i = PIECE_NUM - 2;
									p_pos.pn[PIECE_NUM - 1] = 0;
									p_pos.mn[PIECE_NUM - 1] = 0;
									p_pos.y[PIECE_NUM - 1] = 0;
									p_pos.x[PIECE_NUM - 1] = 0;
									this->bd_pt->deletePiece(p_pos.pn[i] + 1);
									arl_put[p_pos.pn[i]] = false;
								}
								pn = mn = y = 254;
								x = 253;
							}
						}
					}
					if (x != 255) {
						p_pos.x[i] = 0;
					}
				}
				if (y != 255) {
					p_pos.y[i] = 0;
					p_pos.x[i] = 0;
				}
			}
			if (mn != 255) {
				p_pos.mn[i] = 0;
				p_pos.y[i] = 0;
				p_pos.x[i] = 0;
			}
		}
		if (pn != 255) {
			if (i != 0) {
				p_pos.pn[i] = 0;
				p_pos.mn[i] = 0;
				p_pos.y[i] = 0;
				p_pos.x[i] = 0;
				i--;
				this->bd_pt->deletePiece(p_pos.pn[i] + 1);
				arl_put[p_pos.pn[i]] = false;
			}
			else {
				break;
			}
		}
	}
	saveData();
	
	return 0;
}

bool Solver::saveData() {
	writeBinary(SAVE_FILE_ANS, this->answers);

	return true;
}

bool Solver::readData() {
	readBinary(SAVE_FILE_ANS, this->answers);

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
		fin.read((char*)&buf, PIECE_NUM * 4);
		vec.push_back(buf);
	}
	fin.close();
	return true;
}
