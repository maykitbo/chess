#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "structs.h"

class startChessboard : public chessboard {
    private:
        piece rook00 = piece(ROOK, 0, 0, WHITE);
        piece knight10 = piece(KNIGHT, 1, 0, WHITE);
        piece bishop20 = piece(BISHOP, 2, 0, WHITE);
        piece queen30 = piece(QUEEN, 3, 0, WHITE);
        piece king40 = piece(KING, 4, 0, WHITE);
        piece bishop50 = piece(BISHOP, 5, 0, WHITE);
        piece knight60 = piece(KNIGHT, 6, 0, WHITE);
        piece rook70 = piece(ROOK, 7, 0, WHITE);

        piece pawn01 = piece(PAWN, 0, 1, WHITE);
        piece pawn11 = piece(PAWN, 1, 1, WHITE);
        piece pawn21 = piece(PAWN, 2, 1, WHITE);
        piece pawn31 = piece(PAWN, 3, 1, WHITE);
        piece pawn41 = piece(PAWN, 4, 1, WHITE);
        piece pawn51 = piece(PAWN, 5, 1, WHITE);
        piece pawn61 = piece(PAWN, 6, 1, WHITE);
        piece pawn71 = piece(PAWN, 7, 1, WHITE);

        piece pawn06 = piece(PAWN, 0, 6, BLACK);
        piece pawn16 = piece(PAWN, 1, 6, BLACK);
        piece pawn26 = piece(PAWN, 2, 6, BLACK);
        piece pawn36 = piece(PAWN, 3, 6, BLACK);
        piece pawn46 = piece(PAWN, 4, 6, BLACK);
        piece pawn56 = piece(PAWN, 5, 6, BLACK);
        piece pawn66 = piece(PAWN, 6, 6, BLACK);
        piece pawn76 = piece(PAWN, 7, 6, BLACK);

        piece rook07 = piece(ROOK, 0, 7, BLACK);
        piece knight17 = piece(KNIGHT, 1, 7, BLACK);
        piece bishop27 = piece(BISHOP, 2, 7, BLACK);
        piece queen37 = piece(QUEEN, 3, 7, BLACK);
        piece king47 = piece(KING, 4, 7, BLACK);
        piece bishop57 = piece(BISHOP, 5, 7, BLACK);
        piece knight67 = piece(KNIGHT, 6, 7, BLACK);
        piece rook77 = piece(ROOK, 7, 7, BLACK);
        void piecesArrey();
        void globalDepth(int level);
        void oneMove(moveYT one);
        bool castlingMove(moveYT one);
        void enPassantMove(int8_t startX, int8_t startY, int8_t endX, int8_t endY);
        void passPawnMove(moveYT one, int8_t passedPawnName);
        void oneColorOffCastling(int8_t color);
        template<class T>
        bool moveToCheck(moveYT move) {
            // botColor = botColor == WHITE ? BLACK : WHITE;
            T buff(*this, move);
            bool R = buff.findMoves(botColor == WHITE ? BLACK : WHITE);
            buff.ret.clear();
            // botColor = botColor == WHITE ? BLACK : WHITE;
            return R;
        }
        void log_speed(double sec);
        void castlingOffCheck(int8_t color);
    public:
        startChessboard(int8_t botColor);
        startChessboard() : startChessboard(WHITE) {}
        int8_t humanMove(moveYT hm, int8_t passedPawnName);
        void newStart(int8_t color, int level);
        template<class T>
        void botMove(bool *botWait, T *widget) {
            ret.clear();
            // botColor = botColor == WHITE ? BLACK : WHITE;
            *botWait = 0;
            moveIndex = 0;
            time_t time = clock();
            castlingOffCheck(botColor);
            mapPair result = bestMove();
            if (result.first == CHECKMATE || result.first == STALEMATE) {
                // widget->print(result.first);
                return;
            }
            oneMove(result.second);
            double sec = double(clock() - time) / CLOCKS_PER_SEC;
            // log_speed(sec);                                                                          //// LOG
            *botWait = 1;
            widget->print();
            // botMove<T>(botWait, widget);
        }
};

class boardBuff : public chessboard {
    friend class startChessboard;
    friend class boarBuffCastling;
    friend class chessboard;
    friend class enPassantBoard;
    protected:
        piece add;
    public:
        // mapMove::iterator recurs(chessboard *begin, mapMove::iterator i);
        boardBuff(chessboard &other) : chessboard(other) {}
        template<class T>
        boardBuff(T &other, moveYT move) : chessboard(other) {
            add = piece((other.board[move.startX][move.startY]->getName() == PAWN && (move.endY == 0 || move.endY == 7)) ?\
                        QUEEN : other.board[move.startX][move.startY]->getName(), move.endX, move.endY, other.botColor);
            for (int8_t k = 0; k < 8; ++k) {
                for (int8_t g = 0; g < 8; ++g) {
                    if (g != move.startX || k != move.startY) board[g][k] = other.board[g][k];
                    else board[g][k] = fake;
                }
            }
            board[move.endX][move.endY] = &add;
            if (add.getName() == PAWN && (move.endY - move.startY == 2 || move.endY - move.startY == -2)) {
                enPassantX = add.getX();
            }
        }
};

class boarBuffCastling : public boardBuff {
    friend class startChessboard;
    private:
        piece addKing;
    public:
        template<class T>
        boarBuffCastling(T &other, moveYT move) : boardBuff(other) {
            addKing = piece(KING, move.startX == 0 ? 2 : 6, move.startY, other.botColor);
            add = piece(ROOK, move.startX == 0 ? 3 : 5, move.startY, other.botColor);
            for (int8_t k = 0; k < 8; ++k) {
                for (int8_t g = 0; g < 8; ++g) {
                    if (!(g == move.startX && k == move.startY) && !(g == 4 && k == move.startY)) board[g][k] = other.board[g][k];
                    else board[g][k] = fake;
                }
            }
            board[addKing.getX()][addKing.getY()] = &addKing;
            board[add.getX()][add.getY()] = &add;
        }

};

class enPassantBoard : public boardBuff {
    friend class startChessboard;
    public:
        template<class T>
        enPassantBoard(T &other, moveYT move) : boardBuff(other) {
            add = piece(PAWN, other.enPassantX, move.endY, other.botColor);
            for (int8_t k = 0; k < 8; ++k) {
                for (int8_t g = 0; g < 8; ++g) {
                    if (!(g == move.startX && k == move.startY) && !(g == other.enPassantX && k == (botColor == WHITE ? 3 : 4)))
                        board[g][k] = other.board[g][k];
                    else
                        board[g][k] = fake;
                }
            }
            board[other.enPassantX][move.endY] = &add;
        }
};

#endif  // CHESSBOARD_H
