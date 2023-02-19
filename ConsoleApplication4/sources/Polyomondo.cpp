// ConsoleApplication4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "AdvPieces.h"
#include "Pieces.h"
#include "Piece.h"
#include "Printer.h"
#include "Board.h"
#include "Solver.h"
#include "CSVHandler.h"

int main()
{
    AdvPieces adv_pieces;
    Pieces pieces, pieces_buf;
    Piece piece_buf, pb2;
    int i, j, k, pieces_num;
    Piece* pt;
    Printer printer("test_window", FIG_WIDTH, FIG_HEIGHT);
    Board board;
    Solver solver(&adv_pieces, &board);

    // load data
    pieces.loadPieces(PIECES_CSV_FNAME, PIECE_NUM);
    //pieces.printPieces();

    // save rotation pieces and flip pieces
    for (i = 0; i < PIECE_NUM; i++) {
        piece_buf = pieces.getPiece(i);
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 6; k++) {
                pieces_buf.addPiece(piece_buf);
                piece_buf.rotatePiece();
            }
            piece_buf.flipPiece();
        }
        adv_pieces.addPieces(pieces_buf);
        while (pieces_buf.size() > 0) {
            pieces_buf.delPiece(0);
        }
    }/*
    std::cout << adv_pieces.getPieces(PIECE_NUM - 1).size();
    adv_pieces.delPiece(PIECE_NUM-1, 11);
    std::cout << adv_pieces.getPieces(PIECE_NUM-1).size();*/
    //adv_pieces.printAdvPieces();

    // delete same shape
    for (i = 0; i < adv_pieces.size(); i++) {
        pieces_num = adv_pieces.getPieces(i).size();
        j = 0;
        while (j < pieces_num) {
            for (k = pieces_num - 1 - j; k > 0; k--) {
                //std::cout << "( " << j << ", " << j + k << " ), ";
                pieces_buf = adv_pieces.getPieces(i);
                piece_buf.setFig(pieces_buf.getPiece(j).getFig());
                //piece_buf.printPiece();
                //piece_buf.printPiece2(pieces_buf.getPiece(j + k).getFig());
                if (piece_buf.figEqual(pieces_buf.getPiece(j + k).getFig())) {
                    adv_pieces.delPiece(i, j + k);
                    pieces_num--;
                }
            }
            std::cout << "\n";
            j++;
        }
    }

    
    // print Pieces
    //adv_pieces.printAdvPieces();
    //for (i = 0; i < adv_pieces.size(); i++) {
    //    for (j = 0; j < adv_pieces.getPieces(i).size(); j++) {
    //        printer.print((uint8_t *)adv_pieces.getPieces(i).getPiece(j).getFig(), 0);
    //    }
    //}
    

    board.loadBoard(INITIALBOARD_CSV_FNAME);
    /*
    for (i = 0; i < BOARD_HEIGHT; i++) {
        for (j = 0; j < BOARD_WIDTH; j+=2) {
            board.putPiece(adv_pieces.getPieces(0).getPiece(0).getFig(), j, i);
            board.printBoard(100);
            board.deletePiece(1);
        }
    }*/

    
    solver.solve();
    
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
