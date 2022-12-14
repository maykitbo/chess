#ifndef CHESS_DEFINES_H
#define CHESS_DEFINES_H

// #define DEPTH 7
// #define SMALL_DEPTH 4

// int8_t DEPTH = 5;
// int8_t SMALL_DEPTH = 2;

#define LOGGG true             // on off logs

#define CASTLING 10
#define ENPASSANT 11

#define A_ 0
#define B_ 1
#define C_ 2
#define D_ 3
#define E_ 4
#define F_ 5
#define G_ 6
#define H_ 7

#define LOG_NAME "no lists of pieces"

#define ONE_POSSIBLE_MOVE 60
#define SUM_MOVES_KOEF 20

#define BLACK false
#define WHITE true

#define P_WHITE 1
#define P_BLACK -1

#define PAWN 1
#define BISHOP 2
#define KNIGHT 3
#define ROOK 4
#define QUEEN 5
#define KING 6

#define P_PAWN 100
#define P_BISHOP 230
#define P_KNIGHT 216
#define P_ROOK 355
#define P_QUEEN 762
#define P_KING INT16_MAX

#define P_CHECK 60

#define CHECKMATE INT16_MIN
#define STALEMATE INT16_MIN + 1

#endif  // CHESS_DEFINES_H
