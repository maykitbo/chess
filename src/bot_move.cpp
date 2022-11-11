#include "chessboard.h"

const int8_t pawnSquarePrice[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, \
                         {5, 10, 10, -20, -20, 10, 10, 5}, \
                         {5, -5, -10, 0, 0, -10, -5, 5}, \
                         {0, 0, 0, 20, 20, 0, 0, 0}, \
                         {5, 5, 10, 25, 25, 10, 5, 5}, \
                         {10, 10, 20, 30, 30, 20, 10, 10}, \
                         {50, 50, 50, 50, 50, 50, 50, 50}, \
                         {0, 0, 0, 0, 0, 0, 0, 0}};                     
const int8_t rookSquarePrice[8][8] = {{0, 0, 0, 5, 5, 0, 0, 0}, \
                         {-5, 0, 0, 0, 0, 0, 0, -5}, \
                         {-5, 0, 0, 0, 0, 0, 0, -5}, \
                         {-5, 0, 0, 0, 0, 0, 0, -5}, \
                         {-5, 0, 0, 0, 0, 0, 0, -5}, \
                         {-5, 0, 0, 0, 0, 0, 0, -5}, \
                         {5, 10, 10, 10, 10, 10, 10, 5}, \
                         {0, 0, 0, 0, 0, 0, 0, 0}};
const int8_t knightSquarePrice[8][8] = {{-50, -40, -30, -30, -30, -30, -40, -50}, \
                         {-40, -20, 0, 5, 5, 0, -20, -40}, \
                         {-30, 5, 10, 15, 15, 10, 5, -30}, \
                         {-30, 0, 15, 20, 20, 15, 0, -30}, \
                         {-30, 5, 15, 20, 20, 25, 5, -30}, \
                         {-30, 0, 10, 15, 15, 10, 0, -30}, \
                         {-40, -20, 0, 0, 0, 0, -20, -40}, \
                         {-50, -40, -30, -30, -30, -30, -40, -50}};
const int8_t bishopSquarePrice[8][8] = {{-20, -10, -10, -10, -10, -10, -10, -20}, \
                         {-10, 5, 0, 0, 0, 0, 5, -10}, \
                         {-10, 10, 10, 10, 10, 10, 10, -10}, \
                         {-10, 0, 10, 10, 10, 10, 0, -10}, \
                         {-10, 5, 5, 10, 10, 5, 5, -10}, \
                         {-10, 0, 5, 10, 10, 5, 0, -10}, \
                         {-10, 0, 0, 0, 0, 0, 0, -10}, \
                         {-20, -10, -10, -10, -10, -10, -10, -20}};
const int8_t queenSquarePrice[8][8] = {{-20, -10, -10, -5, -5, -10, -10, -20}, \
                         {-10, 0, 5, 0, 0, 5, 0, -10}, \
                         {-10, 5, 5, 5, 5, 5, 5, -10}, \
                         {0, 0, 5, 5, 5, 5, 0, 0}, \
                         {-5, 0, 5, 5, 5, 5, 0, -5}, \
                         {-10, 0, 5, 5, 5, 5, 0, -10}, \
                         {-10, 0, 0, 0, 0, 0, 0, -10}, \
                         {-20, -10, -10, -5, -5, -10, -10, -20}};
const int8_t kingSquarePrice[8][8] = {{20, 30, 10, 0, 0, 10, 30, 20}, \
                                {20, 20, 0, 0, 0, 0, 20, 20}, \
                                {-10, -20, -20, -20, -20, -20, -20, -10}, \
                                {-20, -30, -30, -40, -40, -30, -30, -20}, \
                                {-30, -40, -40, -50, -50, -40, -40, -30}, \
                                {-30, -40, -40, -50, -50, -40, -40, -30}, \
                                {-30, -40, -40, -50, -50, -40, -40, -30}, \
                                {-30, -40, -40, -50, -50, -40, -40, -30}};

mapPair chessboard::bestMove() {
    if (findMoves()) return mapPair(P_KING, moveYT(0, 0, 0, 0));
    if (ret.size() == 0) return mapPair(STALEMATE, moveYT(0, 0, 0, 0));
    if (ret.size() == 1) return (*ret.begin());
    if (depth < global::depth) {
        for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
            if ((*i).first < P_PAWN - 30 && depth > global::small_depth) {
                ++i;
                continue;
            }
            i = createBuffBoard(i);
        }
    }
    if (ret.size() == 1) return (*ret.begin());
    if (ret.size() == 0) return mapPair(CHECKMATE, moveYT(0, 0, 0, 0));
    return dearestMapMove();
}

mapPair chessboard::dearestMapMove() {
    auto rex = ret.begin();
    for (auto i = ++ret.begin(); i != ret.end(); ++i) {
        if ((*i).first > (*rex).first) rex = i;
    }
    return *rex;
}

bool chessboard::findMoves() {
    auto iter = ret.begin();
    for (uint8_t k = 0; k < 8; ++k) {
        for (uint8_t g = 0; g < 8; ++g) {
            if (board[g][k] != fake && board[g][k]->getColor() == botColor) {
                // try { board[g][k]->Pmove(this); }
                // catch(...) { return mapPair(P_KING, moveYT(0, 0, 0, 0)); }
                board[g][k]->Pmove(this);
                for ( ; iter != ret.end(); iter++) {
                    if ((*iter).first > P_KING - 100) return true;
                }
            }
        }
    }
    return false;
}

mapMove::iterator chessboard::createBuffBoard(mapMove::iterator i) {
    switch ((*i).second.endX) {
        case CASTLING:
            return recurs<boarBuffCastling>(i);
        case ENPASSANT:
            return recurs<enPassantBoard>(i);
        default:
            return recurs<boardBuff>(i);
    }
}

int8_t chessboard::squarePrice(int8_t startX, int8_t startY, int8_t endX, int8_t endY) const {
    int8_t kof = (botColor == WHITE ? 1 : (-1));
    int8_t pl = (botColor == WHITE ? 0 : (7));
    if (endX == CASTLING) {
        return squerePriceSwitch(startX == 0 ? 3 : 5, pl + startY * kof, ROOK) +\
                squerePriceSwitch(startX == 0 ? 2 : 6, pl + startY * kof, KING) -\
                squerePriceSwitch(startX, pl + startY * kof, ROOK) -\
                squerePriceSwitch(4, pl + startY * kof, KING);
    }
    return squerePriceSwitch(endX, pl + endY * kof, board[startX][startY]->getName()) -\
            squerePriceSwitch(startX, pl + startY * kof, board[startX][startY]->getName());
}

int8_t chessboard::squerePriceSwitch(int8_t x, int8_t y, int8_t name) const {
    switch (name) {
        case PAWN:
            return pawnSquarePrice[x][y];
        case BISHOP:
            return bishopSquarePrice[x][y];
        case ROOK:
            return rookSquarePrice[x][y];
        case KNIGHT:
            return knightSquarePrice[x][y];
        case KING:
            return kingSquarePrice[x][y];
        case QUEEN:
            return queenSquarePrice[x][y];
    }
    return 0;
}
