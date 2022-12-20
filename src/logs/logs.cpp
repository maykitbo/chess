#include "../model/chessboard.h"

void startChessboard::log_speed(double sec, moveYT move) {
    ofstream file;
    file.open("log_speed.txt", ios_base::app);
    file << "depth = " << (int)global::depth << "/" << (int)global::small_depth << "  //  move index = ";
    file.width(9);
    file.setf(ios::left);
    file << moveIndex;
    file << "  //  time = ";
    file.width(9);
    file.setf(ios::left);
    file << sec;
    file << "  //  one iter time = ";
    file.width(20);
    file.setf(ios::left);
    file << sec / moveIndex;
    file << "  <----  " << LOG_NAME << "  " << (int)move.startX << ":" << (int)move.startY << " - " << (int)move.endX << ":" << (int)move.endY << "\n";
    file.close();
}

void startChessboard::human_log(moveYT move) {
    ofstream file;
    file.open("log_speed.txt", ios_base::app);
    file << "Human:   " << (int)move.startX << ":" << (int)move.startY << " - " << (int)move.endX << ":" << (int)move.endY << "\n";
}