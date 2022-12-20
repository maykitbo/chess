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
        void newPassPawnBoard(bool color, int level);
        void globalDepth(int level);
        void oneMove(moveYT one);
        bool castlingMove(moveYT one);
        void enPassantMove(int8_t startX, int8_t startY, int8_t endX, int8_t endY);
        void passPawnMove(moveYT one, int8_t passedPawnName);
        void oneColorOffCastling(bool color);
        template<class T>
        bool moveToCheck(moveYT move) {
            botColor = !botColor;
            T buff(*this, move);
            botColor = !botColor;
            bool R = buff.findMoves(botColor);
            buff.ret.clear();
            return R;
        }
        void log_speed(double sec, moveYT move);
        void human_log(moveYT move);
        void castlingOffCheck(bool color);

        // listPiece whiteList;
        // listPiece blackList;

    public:
        startChessboard(bool botColor);
        startChessboard() : startChessboard(WHITE) {}
        int8_t humanMove(moveYT hm, int8_t passedPawnName);
        void newStart(bool color, int level);
        template<class T>
        void botMove(bool *botWait, T *widget) {
            ret.clear();
            *botWait = 0;
            sumMoves = 0;
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
            if (LOGGG) log_speed(sec, result.second);                                                                          //// LOG
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
            cycleBase([&](int8_t g, int8_t k) {
                if (g != move.startX || k != move.startY) board[g][k] = other.board[g][k];
                else board[g][k] = fake;
            });
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
            cycleBase([&](int8_t g, int8_t k) {
                if (!(g == move.startX && k == move.startY) && !(g == 4 && k == move.startY)) board[g][k] = other.board[g][k];
                else board[g][k] = fake;
            });
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
            cycleBase([&](int8_t g, int8_t k) {
                if (!(g == move.startX && k == move.startY) && !(g == other.enPassantX && k == (botColor == WHITE ? 3 : 4)))
                    board[g][k] = other.board[g][k];
                else
                    board[g][k] = fake;
            });
            board[other.enPassantX][move.endY] = &add;
        }
};

#endif  // CHESSBOARD_H
