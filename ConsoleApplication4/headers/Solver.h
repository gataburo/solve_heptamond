#include "AdvPieces.h"
#include "Board.h"
#include <time.h>

typedef struct {
	uint8_t	pn[PIECE_NUM];
	uint8_t mn[PIECE_NUM];
	uint8_t y[PIECE_NUM];
	uint8_t x[PIECE_NUM];
}PIECE_POS;

class Solver {
private:
	AdvPieces* adv_pcs_pt;
	Board* bd_pt;
	std::vector<PIECE_POS> answers;
public:
	Solver(AdvPieces* adv_pcs_pt_pt, Board* bd_pt);
	uint8_t solve();
private:
	bool saveData();
	bool readData();
	bool writeBinary(std::string filepath, std::vector<PIECE_POS>& vec);
	bool readBinary(std::string filepath, std::vector<PIECE_POS>& vec);
};
