#ifndef STRUCTS_H
#define STRUCTS_H

#include "chess_defines.h"

#include <vector>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
//#include "structs.h"
#include <math.h>
#include <ctime>
// #include <math.h>

using namespace std;

namespace global {
    extern int8_t depth;
    extern int8_t small_depth;
}

class boardBuff;
class boarBuffCastling;
class enPassantBoard;
class piece;

struct moveYT {
    int8_t startX, startY, endX, endY;
    moveYT(int8_t endX, int8_t endY, int8_t startX, int8_t startY) : startX(startX), startY(startY), endX(endX), endY(endY) {}
    moveYT() : startX(0), startY(0), endX(0), endY(0) {}
};

using mapPair = pair<int16_t, moveYT>;
using mapMove = list<mapPair>;
using listMove = list<moveYT>;
using listPiece = list<piece*>;

class chessboard {
    friend class boardBuff;
    friend class boarBuffCastling;
    friend class enPassantBoard;
    protected:
        bool castling00, castling07, castling70, castling77;
        int8_t enPassantX;
        int8_t botColor;
        mapMove ret;
        int8_t depth = 0;
        unsigned int moveIndex = 0;
        int sumMoves = 0;
    public:
        class piece {
            private:
                chessboard *Qch;
                int8_t name, xLit, yNum, color;
                int16_t price;
                void pawnMove();
                void bishopMove();
                void knightMove();
                void rookMove();
                void queenMove();
                void kingMove();
                void bishopRook(int8_t Xznak, int8_t Yznak);
                void coolInsert(int8_t x, int8_t y, int16_t value);
                int16_t checkSquare(int8_t x, int8_t y);
                bool castling(int8_t x, int8_t y);
            public:
                piece() : name(0), xLit(0), yNum(0), color(0), Qch(nullptr) {}
                piece(int8_t name_, int8_t x, int8_t y, int8_t color_);
                void dropp(int8_t x, int8_t y);
                void dropp(int8_t name_, int8_t x, int8_t y);
                void Pmove(chessboard *owner);
                int8_t getName() const { return name; }
                int8_t &setName() { return name; }
                int8_t getColor() const { return color; }
                int8_t getX() const { return xLit; }
                int8_t getY() const { return yNum; }
                int8_t &setX() {return xLit; }
                int8_t &setY() {return yNum; }
                int16_t getPrice() const { return price; }
        };
    protected:
        piece *board[8][8];
        piece *fake = nullptr;
    public:
        chessboard() = default;
        chessboard(int8_t botClr) : botColor(botClr), castling00(true), castling07(true), castling70(true), castling77(true), enPassantX(-1) {}
        chessboard(chessboard &other) : botColor(other.botColor == WHITE ? BLACK : WHITE), castling00(other.castling00), \
            castling07(other.castling07), castling70(other.castling70), castling77(other.castling77), depth(other.depth + 1), enPassantX(-1) {}
        piece *operator()(int8_t x, int8_t y) const { return board[x][y]; }
        piece *vacant() const { return fake; }
        int8_t squarePrice(int8_t startX, int8_t startY, int8_t endX, int8_t endY) const;
        int8_t squerePriceSwitch(int8_t x, int8_t y, int8_t name) const;
        mapPair bestMove();
        bool findMoves();
        bool findMoves(int8_t color);
        mapPair dearestMapMove();
        mapMove::iterator createBuffBoard(mapMove::iterator i);
        template<class T>
        mapMove::iterator recurs(mapMove::iterator i) {
            T buff(*this, (*i).second);
            int16_t movePrice = (buff.bestMove()).first;
            if (movePrice > P_KING - 100) {
                moveIndex += buff.moveIndex;
                return ret.erase(i);
            } else {
                (*i).first -= movePrice;
                moveIndex += buff.moveIndex;
                return ++i;
            }
        }
};

#endif  // STRUCTS_H
