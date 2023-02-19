#pragma once

#define PIECE_SIZE 7
#define HRF_PIECE_SIZE 4 // (int(PIECE_SIZE / 2) + 1)
#define PIECE_NUM 24
#define FIG_HEIGHT HRF_PIECE_SIZE
#define FIG_WIDTH (PIECE_SIZE+1)	// ���������̂܂ܓW�J����邽�ߊ��ʂ��Ȃ��ƁA�o�O���ĂԁB(3*FIG_WIDTH�Ƃ����ꍇ�ɁA���ʂ��Ȃ���3*PIECE_SIZE+1�ƂȂ�)
#define BOARD_HEIGHT 12
#define BOARD_WIDTH 24
#define HASH_MAX 8192

#define PIECES_CSV_FNAME "./resouces/Pieces.csv"
#define INITIALBOARD_CSV_FNAME "./resouces/Board.csv"
#define SAVE_FILE_ANS "./resouces/save/Answer.bin"
#define SAVE_FILE_TRY "./resouces/save/Tried"	// �t�@�C������������邽�߁A�g���q�͌�ł��Ă���

