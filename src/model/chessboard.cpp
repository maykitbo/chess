#include "chessboard.h"
#include <iostream>

startChessboard::startChessboard(bool botColor) : chessboard(botColor) {
    cycleBase([&](int8_t g, int8_t k) {
        board[g][k] = fake;
    });
}

void startChessboard::newStart(bool color, int level) {
    // return newPassPawnBoard(color, level);                                   //// 2 Pawn 2 King
    globalDepth(level);
    botColor = color;
    board[0][0] = rook00.dropp(0, 0);
    board[1][0] = knight10.dropp(1, 0);
    board[2][0] = bishop20.dropp(2, 0);
    board[3][0] = queen30.dropp(3, 0);
    board[4][0] = king40.dropp(4, 0);
    board[5][0] = bishop50.dropp(5, 0);
    board[6][0] = knight60.dropp(6, 0);
    board[7][0] = rook70.dropp(7, 0);
    board[0][1] = pawn01.dropp(PAWN, 0, 1);
    board[1][1] = pawn11.dropp(PAWN, 1, 1);
    board[2][1] = pawn21.dropp(PAWN, 2, 1);
    board[3][1] = pawn31.dropp(PAWN, 3, 1);
    board[4][1] = pawn41.dropp(PAWN, 4, 1);
    board[5][1] = pawn51.dropp(PAWN, 5, 1);
    board[6][1] = pawn61.dropp(PAWN, 6, 1);
    board[7][1] = pawn71.dropp(PAWN, 7, 1);
    board[0][6] = pawn06.dropp(PAWN, 0, 6);
    board[1][6] = pawn16.dropp(PAWN, 1, 6);
    board[2][6] = pawn26.dropp(PAWN, 2, 6);
    board[3][6] = pawn36.dropp(PAWN, 3, 6);
    board[4][6] = pawn46.dropp(PAWN, 4, 6);
    board[5][6] = pawn56.dropp(PAWN, 5, 6);
    board[6][6] = pawn66.dropp(PAWN, 6, 6);
    board[7][6] = pawn76.dropp(PAWN, 7, 6);
    board[0][7] = rook07.dropp(0, 7);
    board[1][7] = knight17.dropp(1, 7);
    board[2][7] = bishop27.dropp(2, 7);
    board[3][7] = queen37.dropp(3, 7);
    board[4][7] = king47.dropp(4, 7);
    board[5][7] = bishop57.dropp(5, 7);
    board[6][7] = knight67.dropp(6, 7);
    board[7][7] = rook77.dropp(7, 7);
    cycleStart([&](int8_t g, int8_t k) {
        board[g][k] = fake;
    });
}

void startChessboard::globalDepth(int level) {
    switch (level) {
    case 1:
        global::depth = 1;
        global::small_depth = 1;
        break;
    case 2:
        global::depth = 4;
        global::small_depth = 2;
        break;
    case 3:
        global::depth = 5;
        global::small_depth = 3;
        break;
    case 4:
        global::depth = 6;
        global::small_depth = 3;
        break;
    case 5:
        global::depth = 7;
        global::small_depth = 3;
        break;
    }
}

void startChessboard::newPassPawnBoard(bool color, int level) {
    globalDepth(level);
    botColor = color;
    pawn01.dropp(PAWN, 1, 6);
    pawn06.dropp(PAWN, 6, 2);
    king40.dropp(0, 5);
    king47.dropp(7, 3);
    cycleBase([&](int8_t g, int8_t k) {
        board[g][k] = fake;
    });
    board[1][6] = &pawn01;
    board[6][2] = &pawn06;
    board[0][5] = &king40;
    board[7][3] = &king47;
}

// void startChessboard::log_speed(double sec, moveYT move) {
//     ofstream file;
//     file.open("log_speed.txt", ios_base::app);
//     file << "depth = " << (int)global::depth << "/" << (int)global::small_depth << "  //  move index = ";
//     file.width(9);
//     file.setf(ios::left);
//     file << moveIndex;
//     file << "  //  time = ";
//     file.width(9);
//     file.setf(ios::left);
//     file << sec;
//     file << "  //  one iter time = ";
//     file.width(20);
//     file.setf(ios::left);
//     file << sec / moveIndex;
//     file << "  <----  " << LOG_NAME << "  " << (int)move.startX << ":" << (int)move.startY << " - " << (int)move.endX << ":" << (int)move.endY << "\n";
//     file.close();
// }

// void startChessboard::human_log(moveYT move) {
//     ofstream file;
//     file.open("log_speed.txt", ios_base::app);
//     file << "Human:   " << (int)move.startX << ":" << (int)move.startY << " - " << (int)move.endX << ":" << (int)move.endY << "\n";
// }
