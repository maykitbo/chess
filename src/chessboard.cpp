#include "chessboard.h"
#include <iostream>

startChessboard::startChessboard(int8_t botColor) : chessboard(botColor) {
    piecesArrey();
}

void startChessboard::newStart(int8_t color, int level) {
    globalDepth(level);
    botColor = color;
    rook00.dropp(0, 0);
    knight10.dropp(1, 0);
    bishop20.dropp(2, 0);
    queen30.dropp(3, 0);
    king40.dropp(4, 0);
    bishop50.dropp(5, 0);
    knight60.dropp(6, 0);
    rook70.dropp(7, 0);
    pawn01.dropp(PAWN, 0, 1);
    pawn11.dropp(PAWN, 1, 1);
    pawn21.dropp(PAWN, 2, 1);
    pawn31.dropp(PAWN, 3, 1);
    pawn41.dropp(PAWN, 4, 1);
    pawn51.dropp(PAWN, 5, 1);
    pawn61.dropp(PAWN, 6, 1);
    pawn71.dropp(PAWN, 7, 1);
    pawn06.dropp(PAWN, 0, 6);
    pawn16.dropp(PAWN, 1, 6);
    pawn26.dropp(PAWN, 2, 6);
    pawn36.dropp(PAWN, 3, 6);
    pawn46.dropp(PAWN, 4, 6);
    pawn56.dropp(PAWN, 5, 6);
    pawn66.dropp(PAWN, 6, 6);
    pawn76.dropp(PAWN, 7, 6);
    rook07.dropp(0, 7);
    knight17.dropp(1, 7);
    bishop27.dropp(2, 7);
    queen37.dropp(3, 7);
    king47.dropp(4, 7);
    bishop57.dropp(5, 7);
    knight67.dropp(6, 7);
    rook77.dropp(7, 7);
    piecesArrey();
}

void startChessboard::globalDepth(int level) {
    switch (level) {
    case 1:
        global::depth = 3;
        global::small_depth = 1;
        break;
    case 2:
        global::depth = 4;
        global::small_depth = 2;
        break;
    case 3:
        global::depth = 5;
        global::small_depth = 2;
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

void startChessboard::piecesArrey() {
    board[0][0] = &rook00;
    board[1][0] = &knight10;
    board[2][0] = &bishop20;
    board[3][0] = &queen30;
    board[4][0] = &king40;
    board[5][0] = &bishop50;
    board[6][0] = &knight60;
    board[7][0] = &rook70;
    board[0][1] = &pawn01;
    board[1][1] = &pawn11;
    board[2][1] = &pawn21;
    board[3][1] = &pawn31;
    board[4][1] = &pawn41;
    board[5][1] = &pawn51;
    board[6][1] = &pawn61;
    board[7][1] = &pawn71;
    board[0][6] = &pawn06;
    board[1][6] = &pawn16;
    board[2][6] = &pawn26;
    board[3][6] = &pawn36;
    board[4][6] = &pawn46;
    board[5][6] = &pawn56;
    board[6][6] = &pawn66;
    board[7][6] = &pawn76;
    board[0][7] = &rook07;
    board[1][7] = &knight17;
    board[2][7] = &bishop27;
    board[3][7] = &queen37;
    board[4][7] = &king47;
    board[5][7] = &bishop57;
    board[6][7] = &knight67;
    board[7][7] = &rook77;
    for (int8_t k = 2; k < 6; k++) {
        for (int8_t g = 0; g < 8; g++) {
            board[g][k] = fake;
        }
    }
}

// startChessboard &startChessboard::operator=(startChessboard &&sCh) {
//     rook00 = sCh.rook00;
//     knight10 = sCh.knight10;
//     bishop20 = sCh.bishop20;
//     queen30 = sCh.queen30;
//     king40 = sCh.king40;
//     bishop50 = sCh.bishop50;
//     knight60 = sCh.knight60;
//     rook70 = sCh.rook70;
//     pawn01 = sCh.pawn01;
//     pawn11 = sCh.pawn11;
//     pawn21 = sCh.pawn21;
//     pawn31 = sCh.pawn31;
//     pawn41 = sCh.pawn41;
//     pawn51 = sCh.pawn51;
//     pawn61 = sCh.pawn61;
//     pawn71 = sCh.pawn71;
//     pawn06 = sCh.pawn06;
//     pawn16 = sCh.pawn16;
//     pawn26 = sCh.pawn26;
//     pawn36 = sCh.pawn36;
//     pawn46 = sCh.pawn46;
//     pawn56 = sCh.pawn56;
//     pawn66 = sCh.pawn66;
//     pawn76 = sCh.pawn76;
//     rook07 = sCh.rook07;
//     knight17 = sCh.knight17;
//     bishop27 = sCh.bishop27;
//     queen37 = sCh.queen37;
//     king47 = sCh.king47;
//     bishop57 = sCh.bishop57;
//     knight67 = sCh.knight67;
//     rook77 = sCh.rook77;
//     board[0][0] = &rook00;
//     board[1][0] = &knight10;
//     board[2][0] = &bishop20;
//     board[3][0] = &queen30;
//     board[4][0] = &king40;
//     board[5][0] = &bishop50;
//     board[6][0] = &knight60;
//     board[7][0] = &rook70;
//     board[0][1] = &pawn01;
//     board[1][1] = &pawn11;
//     board[2][1] = &pawn21;
//     board[3][1] = &pawn31;
//     board[4][1] = &pawn41;
//     board[5][1] = &pawn51;
//     board[6][1] = &pawn61;
//     board[7][1] = &pawn71;
//     board[0][6] = &pawn06;
//     board[1][6] = &pawn16;
//     board[2][6] = &pawn26;
//     board[3][6] = &pawn36;
//     board[4][6] = &pawn46;
//     board[5][6] = &pawn56;
//     board[6][6] = &pawn66;
//     board[7][6] = &pawn76;
//     board[0][7] = &rook07;
//     board[1][7] = &knight17;
//     board[2][7] = &bishop27;
//     board[3][7] = &queen37;
//     board[4][7] = &king47;
//     board[5][7] = &bishop57;
//     board[6][7] = &knight67;
//     board[7][7] = &rook77;
//     for (int8_t k = 2; k < 6; k++) {
//         for (int8_t g = 0; g < 8; g++) {
//             board[g][k] = fake;
//         }
//     }
// }

void startChessboard::log_speed(double sec) {
    ofstream file;
    file.open("log_speed.txt", ios_base::app);
    file << "depth = " << global::depth << "/" << global::small_depth << "  //  move index = ";
    file.width(9);
    file.setf(ios::left);
    file << moveIndex;
    file << "  //  time = ";
    file.width(9);
    file.setf(ios::left);
    file << sec;
    file << "  //  one iter time = ";
    file.width(20);
    file.setf(ios::left);
    file << sec / moveIndex;
    file << "  <----  " << LOG_NAME << "\n";
    file.close();
}
