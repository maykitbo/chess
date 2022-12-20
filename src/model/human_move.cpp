#include "chessboard.h"

int8_t startChessboard::humanMove(moveYT hm, int8_t passedPawnName) {  // return 0 - move impossible; return 1 - move done; return 2 - need passed pawn name
    ret.clear();
    // castlingOffCheck(botColor == WHITE ? BLACK : WHITE);
    castlingOffCheck(!botColor);
    int8_t R = 0;
    board[hm.startX][hm.startY]->Pmove(this);
    for (auto i = ret.begin(); i != ret.end(); i++) {
        if (i->second.endX == hm.endX && i->second.endY == hm.endY) {
            if (moveToCheck<boardBuff>(hm)) return R;                                           //// return move to check
            if (board[hm.startX][hm.startY]->getName() == PAWN && (i->second.endY == 7 || i->second.endY == 0)) {
                passPawnMove(hm, QUEEN);
                R = 1;
                break;
            }
            R = 1;
            oneMove(hm);
            break;
        } else if (i->second.endX == CASTLING && hm.endX == 4 && board[hm.endX][hm.endY]->getName() == KING && \
                    board[hm.endX][hm.endY]->getColor() == board[hm.startX][hm.startY]->getColor()) {
            if (moveToCheck<boarBuffCastling>(hm)) return R;                                           //// return move to check
            R = 1;
            castlingMove(moveYT(CASTLING, CASTLING, hm.startX, hm.startY));
            break;
        } else if (i->second.endX == ENPASSANT && hm.endX == enPassantX && hm.endY == i->second.endY) {
            if (moveToCheck<enPassantBoard>(hm)) return R;                                           //// return move to check
            enPassantMove(hm.startX, hm.startY, enPassantX, hm.endY);
            R = 1;
            break;
        }
    }
    if (R && LOGGG) human_log(hm);
    // if (ret.size() == 0) {
    //     if (checkBool) return CHECKMATE;
    //     return STALEMATE;
    // }
    // ret.clear();
    return R;
}

void startChessboard::castlingOffCheck(bool color) {
    // if (findMoves(color == WHITE ? BLACK : WHITE)) {
    if (findMoves(!color)) {
        oneColorOffCastling(color);
    }
    ret.clear();
}

bool chessboard::findMoves(bool color) {
    auto iter = ret.begin();
    return cycleBool([&](int8_t g, int8_t k) {
        if (board[g][k] != fake && board[g][k]->getColor() == color) {
            board[g][k]->Pmove(this);
            while (++iter != ret.end()) {
                if ((*iter).first > P_KING - 100) return true;
            }
            --iter;         
        }
        return false;
    });
    // return false;
}
