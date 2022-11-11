// #include "chessboard.h"
#include "structs.h"
#include <iostream>
#include <thread>
#include <future>

const int16_t Price(int8_t name) {
    switch (name) {
        case PAWN:
            return P_PAWN;
        case BISHOP:
            return P_BISHOP;
        case KNIGHT:
            return P_KNIGHT;
        case ROOK:
            return P_ROOK;
        case QUEEN:
            return P_QUEEN;
        case KING:
            return P_KING;
    }
    return 0;
}

chessboard::piece::piece(int8_t name_, int8_t x, int8_t y, int8_t color_) : name(name_), xLit(x), yNum(y), color(color_) {
    price = Price(name);
}

void chessboard::piece::dropp(int8_t x, int8_t y) {
    xLit = x;
    yNum = y;
}

void chessboard::piece::dropp(int8_t name_, int8_t x, int8_t y) {
    name = name_;
    dropp(x, y);
}

void chessboard::piece::Pmove(chessboard *owner) {
    Qch = owner;
    switch (name) {
        case PAWN:
            return pawnMove();
        case BISHOP:
            return bishopMove();
        case KNIGHT:
            return knightMove();
        case ROOK:
            return rookMove();
        case QUEEN:
            return queenMove();
        case KING:
            return kingMove();
    }
}

void chessboard::piece::pawnMove() {
    int16_t value = checkSquare(xLit, yNum + (1 * color));
    if (value == 0) {
        if (yNum == (color == WHITE ? 6 : 1)) {
            value += P_QUEEN - P_PAWN;                 //// passed pawn
        }
        coolInsert(xLit, yNum + (1 * color), value);
        value = checkSquare(xLit, yNum + (2 * color));
        if (yNum == (color == WHITE ? 1 : 6) && (value == 0)) {
            coolInsert(xLit, yNum + (2 * color), value);
        }
    }
    if (Qch->enPassantX != -1 && yNum == (color == WHITE ? 4 : 3) &&\
        (xLit == Qch->enPassantX - 1 || xLit == Qch->enPassantX + 1)) {
        coolInsert(ENPASSANT, color == WHITE ? 5 : 2, P_PAWN);
    }
    value = checkSquare(xLit + 1, yNum + (1 * color));
    if (value > 0) {
        if (yNum == (color == WHITE ? 6 : 1)) {
            value += P_QUEEN - P_PAWN;                 //// passed pawn
        }
        coolInsert(xLit + 1, yNum + (1 * color), value);
    }
    value = checkSquare(xLit - 1, yNum + (1 * color));
    if (value > 0) {
        if (yNum == (color == WHITE ? 6 : 1)) {
            value += P_QUEEN - P_PAWN;                //// passed pawn
        }
        coolInsert(xLit - 1, yNum + (1 * color), value);
    }
}

void chessboard::piece::bishopRook(int8_t Xznak, int8_t Yznak) {
    int8_t k = 1;
    int16_t value = checkSquare(xLit + (k * Xznak), yNum + (k * Yznak));
    while (value > -1) {
        coolInsert(xLit + (k * Xznak), yNum + (k * Yznak), value);
        k++;
        if (value > 0) break;
        value = checkSquare(xLit + (k * Xznak), yNum + (k * Yznak));
    }
}

void chessboard::piece::bishopMove() {
    bishopRook(1, 1);
    bishopRook(-1, -1);
    bishopRook(1, -1);
    bishopRook(-1, 1);
}

void chessboard::piece::knightMove() {
    for (auto k : std::vector<std::pair<int8_t, int8_t>>({{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}})) {
        int16_t value = checkSquare(xLit + k.first, yNum + k.second);
        if (value > -1) {
            coolInsert(xLit + k.first, yNum + k.second, value);
        }
    }
}

void chessboard::piece::rookMove() {
    bishopRook(1, 0);
    bishopRook(-1, 0);
    bishopRook(0, -1);
    bishopRook(0, 1);
    if (castling(xLit, yNum)) {
        coolInsert(CASTLING, CASTLING, 10);    //// castling price
    }
}

void chessboard::piece::queenMove() {
    bishopRook(1, 1);
    bishopRook(-1, -1);
    bishopRook(1, -1);
    bishopRook(-1, 1);
    bishopRook(1, 0);
    bishopRook(-1, 0);
    bishopRook(0, -1);
    bishopRook(0, 1);
}

void chessboard::piece::kingMove() {
    for (auto k : std::vector<std::pair<int8_t, int8_t>>({{1, 0}, {1, 1}, {1, -1}, {0, 1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}})) {
        int16_t value = checkSquare(xLit + k.first, yNum + k.second);
        if (value > -1) {
            coolInsert(xLit + k.first, yNum + k.second, value);
        }
    }
}

int16_t chessboard::piece::checkSquare(int8_t x, int8_t y) {  // проверка клетки: -1 если своя фигура, 0 если пусто, стоимость фигуры если чужая // coordError вернёт -2
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return -2;
    }
    if ((*Qch)(x, y) == Qch->vacant()) {
        return 0;
    }
    if ((*Qch)(x, y)->color == color) {
        return -1;
    }
    // if ((*Qch)(x, y)->price == P_KING) throw (true);
    return (*Qch)(x, y)->price;
}

bool chessboard::piece::castling(int8_t x, int8_t y) {
    if (x == 0 && y == 0 && !checkSquare(1, 0) && !checkSquare(2, 0) && !checkSquare(3, 0)) return Qch->castling00;
    if (x == 0 && y == 7 && !checkSquare(1, 7) && !checkSquare(2, 7) && !checkSquare(3, 7)) return Qch->castling07;
    if (x == 7 && y == 0 && !checkSquare(6, 0) && !checkSquare(5, 0)) return Qch->castling70;
    if (x == 7 && y == 7 && !checkSquare(6, 7) && !checkSquare(5, 7)) return Qch->castling77; 
    return false;
}

void chessboard::piece::coolInsert(int8_t x, int8_t y, int16_t value) {
    value += Qch->squarePrice(xLit, yNum, x, y) / 2;
    Qch->ret.push_back(mapPair(value, moveYT(x, y, xLit, yNum)));
    Qch->moveIndex++;
}
