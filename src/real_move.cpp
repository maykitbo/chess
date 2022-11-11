#include "chessboard.h"

void startChessboard::oneMove(moveYT one) {
    if (one.endX == ENPASSANT) return enPassantMove(one.startX, one.startY, enPassantX, one.endY);
    if (castlingMove(one)) return;
    if (board[one.startX][one.startY]->getName() == PAWN && (one.endY == 7 || one.endY == 0)) {
        return passPawnMove(one, QUEEN);
    }
    board[one.endX][one.endY] = fake;
    board[one.startX][one.startY]->setX() = one.endX;
    board[one.startX][one.startY]->setY() = one.endY;
    board[one.endX][one.endY] = board[one.startX][one.startY];
    board[one.startX][one.startY] = fake;
    if (board[one.endX][one.endY]->getName() == PAWN && (one.endY - one.startY == 2 || one.endY - one.startY == -2))
        enPassantX = one.endX;
    else
        enPassantX = -1;
}

void startChessboard::enPassantMove(int8_t startX, int8_t startY, int8_t endX, int8_t endY) {
    board[endX][endY == 2 ? 3 : 4] = fake;
    board[startX][startY]->setX() = endX;
    board[startX][startY]->setY() = endY;
    board[endX][endY] = board[startX][startY];
    board[startX][startY] = fake;
}

void startChessboard::oneColorOffCastling(int8_t color) {
    switch (color) {
        case WHITE:
            castling00 = false;
            castling70 = false;
            break;
        case BLACK:
            castling07 = false;
            castling77 = false;
            break;
        }
}

bool startChessboard::castlingMove(moveYT one) {
    if (board[one.startX][one.startY]->getName() == KING) {
        oneColorOffCastling(botColor);
        return false;
    }
    if (board[one.startX][one.startY]->getName() == ROOK) {
        if (one.endX == CASTLING) {
            oneColorOffCastling(botColor);
            board[one.startX][one.startY]->setX() = one.startX == 0 ? 3 : 5;
            board[4][one.startY]->setX() = one.startX == 0 ? 2 : 6;
            board[one.startX == 0 ? 3 : 5][one.startY] = board[one.startX][one.startY];
            board[one.startX == 0 ? 2 : 6][one.startY] = board[4][one.startY];
            board[one.startX][one.startY] = fake;
            board[4][one.startY] = fake;
            return true;
        }
        if (one.startX == 0 && one.startY == 0) castling00 = false;
        else if (one.startX == 0 && one.startY == 7) castling07 = false;
        else if (one.startX == 7 && one.startY == 0) castling70 = false;
        else if (one.startX == 7 && one.startY == 7) castling77 = false;
    }
    return false;
}

void startChessboard::passPawnMove(moveYT one, int8_t passedPawnName) {
    board[one.endX][one.endY] == board[one.startX][one.startY];
    board[one.endX][one.endY]->setName() = passedPawnName;
    board[one.endX][one.endY]->setX() = one.endX;
    board[one.endX][one.endY]->setY() = one.endY;
    board[one.startX][one.startY] = fake;
}