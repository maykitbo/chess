#include "chessboard.h"

int8_t startChessboard::humanMove(moveYT hm, int8_t passedPawnName) {  // return 0 - move impossible; return 1 - move done; return 2 - need passed pawn name
    castlingOffCheck(botColor == WHITE ? BLACK : WHITE);
    int8_t R = 0;
    ret.clear();
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
        }
    }
    // if (ret.size() == 0) {
    //     if (checkBool) return CHECKMATE;
    //     return STALEMATE;
    // }
    ret.clear();
    return R;
}

void startChessboard::castlingOffCheck(int8_t color) {
    if (findMoves(color)) oneColorOffCastling(color);
}

bool chessboard::findMoves(int8_t color) {
    auto iter = ret.begin();
    for (uint8_t k = 0; k < 8; ++k) {
        for (uint8_t g = 0; g < 8; ++g) {
            if (board[g][k] != fake && board[g][k]->getColor() == color) {
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

// bool startChessboard::moveToCheck(moveYT move) {
//     botColor = botColor == WHITE ? BLACK : WHITE;
//     boardBuff buff(*this, move);
//     for (int8_t k = 0; k < 8; ++k) {
//         for (int8_t g = 0; g < 8; ++g) {
//             if (buff.board[g][k] != buff.fake && buff.board[g][k]->getColor() != botColor)
//                 buff.board[g][k]->Pmove(&buff);
//         }
//     }
//     for (auto i : buff.ret) {
//         if (i.first > P_KING - 100) {
//             // cout << i.first << " " << (int)i.second.startX << " " << (int)i.second.startY << " " << (int)i.second.endX << " " << (int)i.second.endY << "\n";
//             buff.ret.clear();
//             botColor = botColor == WHITE ? BLACK : WHITE;
//             return true;
//         }
//     }
//     buff.ret.clear();
//     botColor = botColor == WHITE ? BLACK : WHITE;
//     return false;
// }