#pragma once
#include <iostream>
#include "Parameter.h"
#include "Printer.h"

class Board {
private:
	uint8_t area[BOARD_HEIGHT][BOARD_WIDTH];
	Printer printer;
public:
	Board();
	void loadBoard(const char* fname);
	bool putPiece(uint8_t(*fig)[FIG_WIDTH], int x, int y);
	void deletePiece(int fig_num);

	uint8_t(* getArea())[BOARD_WIDTH];
	bool isFilled();
	bool isFragmentation();
	bool allClose(uint8_t (*board_area)[BOARD_WIDTH]);

	void printBoard(int wait_time);
};
