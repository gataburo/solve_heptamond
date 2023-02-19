#include "AdvPieces.h"
#include "Board.h"

typedef struct {
	uint8_t mn[PIECE_NUM];
	uint8_t x[PIECE_NUM];
	uint8_t y[PIECE_NUM];
}PIECE_POS;

class Solver {
private:
	AdvPieces* adv_pcs_pt;
	Board* bd_pt;
	uint8_t put_n;
	PIECE_POS p_pos;
	std::vector<PIECE_POS> answers, tried_list[HASH_MAX];
public:
	Solver(AdvPieces* adv_pcs_pt_pt, Board* bd_pt);
	~Solver();
	uint8_t solve();
	uint8_t recusSolve();
private:
	bool isAllPut();
	bool isInclude(PIECE_POS p_pos, std::vector<PIECE_POS> list);
	uint16_t calcHash();
	bool saveData();
	bool readData();
	bool writeBinary(std::string filepath, std::vector<PIECE_POS>& vec);
	bool readBinary(std::string filepath, std::vector<PIECE_POS>& vec);
};
