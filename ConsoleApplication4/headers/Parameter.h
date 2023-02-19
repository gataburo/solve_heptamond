#pragma once

#define PIECE_SIZE 7
#define HRF_PIECE_SIZE 4 // (int(PIECE_SIZE / 2) + 1)
#define PIECE_NUM 24
#define FIG_HEIGHT HRF_PIECE_SIZE
#define FIG_WIDTH (PIECE_SIZE+1)	// 文字がそのまま展開されるため括弧がないと、バグを呼ぶ。(3*FIG_WIDTHとした場合に、括弧がないと3*PIECE_SIZE+1となる)
#define BOARD_HEIGHT 12
#define BOARD_WIDTH 24
#define HASH_MAX 8192

#define PIECES_CSV_FNAME "./resouces/Pieces.csv"
#define INITIALBOARD_CSV_FNAME "./resouces/Board.csv"
#define SAVE_FILE_ANS "./resouces/save/Answer.bin"
#define SAVE_FILE_TRY "./resouces/save/Tried"	// ファイルが分割されるため、拡張子は後でつけている

