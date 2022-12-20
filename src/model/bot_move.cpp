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
    if (ret.size() == 1 && depth < global::depth - 1) depth = global::depth - 1;

    if (depth < global::depth) {
        for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
            if ((*i).first < P_PAWN - 10 && depth > global::small_depth) {
                ++i;
                continue;
            }
            i = createBuffBoard(i);
        }
    }

    // if (depth <= global::small_depth) {
    //     for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
    //         i = createBuffBoard(i);
    //     }
    // } else if (depth <= global::small_depth + 2 && sumMoves > 3000) {
    //     for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
    //         i = createBuffBoard(i);
    //     }
    // } else if (depth < global::depth) {
    //     for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
    //         if ((*i).first >= P_PAWN - 10) i = createBuffBoard(i);
    //         else ++i;
    //     }
    // }

    // if ((depth + 3) * 500 < sumMoves) {
    //     for (mapMove::iterator i = ret.begin(); i != ret.end(); ) {
    //         i = createBuffBoard(i);
    //     }
    // }

    if (ret.size() == 1) return (*ret.begin());
    if (ret.size() == 0) return mapPair(CHECKMATE, moveYT(0, 0, 0, 0));
    return dearestMapMove();
}

mapPair chessboard::dearestMapMove() {
    auto rex = ret.begin();
    for (auto i = ++ret.begin(); i != ret.end(); ++i) {
        if ((*i).first > (*rex).first) rex = i;
    }
    rex->first += sumMoves / SUM_MOVES_KOEF;                    //// moves sum
    // cout << sumMoves << "\n";
    if (depth == global::depth) rex->first /= 2;                //// last move
    return *rex;
}

bool chessboard::findMoves() {
    auto iter = ret.begin();
    return botCycle([&](int8_t g, int8_t k) {
        board[g][k]->Pmove(this);
        while (++iter != ret.end()) {
            if ((*iter).first > P_KING - 100) return true;
            (*iter).first += squarePrice((*iter).second) / 2;    //// square price
            sumMoves += (*iter).first;                           //// moves sum
        }
        --iter;
        return false;
    });
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

int8_t chessboard::squarePrice(moveYT one) const {
    int8_t kof = (botColor == WHITE ? 1 : (-1));
    int8_t pl = (botColor == WHITE ? 0 : (7));
    if (one.endX == CASTLING) {
        return squerePriceSwitch(one.startX == 0 ? 3 : 5, pl + one.startY * kof, ROOK) +\
                squerePriceSwitch(one.startX == 0 ? 2 : 6, pl + one.startY * kof, KING) -\
                squerePriceSwitch(one.startX, pl + one.startY * kof, ROOK) -\
                squerePriceSwitch(4, pl + one.startY * kof, KING);
    }
    return squerePriceSwitch(one.endX, pl + one.endY * kof, board[one.startX][one.startY]->getName()) -\
            squerePriceSwitch(one.startX, pl + one.startY * kof, board[one.startX][one.startY]->getName());
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
