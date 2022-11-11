#include "widget.h"
#include "./ui_widget.h"
#include <stdlib.h>
#include <QString>
// #include <iostream>
#include <unistd.h>
#include <thread>



Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), oneMove(0, 0, 0, 0), board(0) {
    ui->setupUi(this);

    for (int k = 0; k < 8; k++) {
        for (int g = 0; g < 8; g++) {
            if (ui->gridLayout->itemAtPosition(g, k)) {
                buttons[k][-g + 7] = dynamic_cast<QPushButton*>(ui->gridLayout->itemAtPosition(g, k)->widget());
            }
        }
    }

    for (int k = 0; k < 8; k++) {
        for (int g = 0; g < 8; g++) {
            connect(buttons[g][k], SIGNAL(clicked(bool)), this, SLOT(click()));
        }
    }
    connect(ui->white_b, SIGNAL(clicked(bool)), this, SLOT(startGameW()));
    connect(ui->black_b, SIGNAL(clicked(bool)), this, SLOT(startGameB()));

//    if (BOTCOLOR == WHITE) board.botMove<Widget>(&botWait, this);
    
//    this->print();
}

void Widget::startGameW() {
//    std::cout << "1";
    humanColor = WHITE;
     board.newStart(BLACK, ui->spinBox->value());
//    colRowPrint();
    this->print();
}

void Widget::startGameB() {
//     std::cout << "2";
    board.newStart(WHITE, ui->spinBox->value());
    humanColor = BLACK;
    colRowPrint();
//    board.botMove<Widget>(&botWait, this);
    std::thread thr(&startChessboard::botMove<Widget>, &board, &botWait, this);
    thr.detach();
    this->print();
}

void Widget::colRowPrint() {
    int k = humanColor == WHITE ? 0 : -7;
    ui->label->setText(QString(k + 1));
//    ui->label->setText(QString(k + 1));
}

void Widget::click() {
    if (!botWait || humanColor == 0) return;
    int8_t k = 0, g = 0;
    bool stop = 1;
    for ( ; k < 8 && stop; ++k) {
        for (g = 0; g < 8 && stop; ++g) {
            if (buttons[g][k] == (QPushButton*)sender()) stop = 0;
        }
    }
    --g; --k;
    if (humanColor == BLACK) {
        k = 7 - k;
        g = 7 - g;
    }
//    std::cout << (int)g << " " << (int)k << " " << (int)board(g, k)->getColor() << "\n";
    if (!moveCan && board(g, k) != board.vacant() && board(g, k)->getColor() == humanColor) {
        moveCan = true;
        oneMove.startX = g;
        oneMove.startY = k;
    } else if (moveCan) {
        oneMove.endX = g;
        oneMove.endY = k;
        int hm = board.humanMove(oneMove, 0);
        print();
        if (hm == 1) {
//            std::cout << "123\n";
            std::thread thr(&startChessboard::botMove<Widget>, &board, &botWait, this);
            thr.detach();
            // board.botMove<Widget>(&botWait, this);
        }
        moveCan = false;
    }
}

void Widget::print() {
    if (humanColor == WHITE) {
        for (int k = 0; k < 8; ++k) {
            for (int g = 0; g < 8; ++g) {
                if (board(g, k) != board.vacant()) {
                    buttons[g][k]->setIcon(QIcon("png/" + QString::number(board(g, k)->getName()) + QString::number(board(g, k)->getColor()) + ".png"));
                } else {
                    buttons[g][k]->setIcon(QIcon());
                }
                buttons[g][k]->setIconSize(QSize(65, 65));
            }
        }
   } else {
        for (int k = 0; k < 8; ++k) {
            for (int g = 0; g < 8; ++g) {
                if (board(g, k) != board.vacant()) {
                    buttons[7 - g][7 - k]->setIcon(QIcon("png/" + QString::number(board(g, k)->getName()) + QString::number(board(g, k)->getColor()) + ".png"));
                } else {
                    buttons[7 - g][7 - k]->setIcon(QIcon());
                }
                buttons[7 - g][7 - k]->setIconSize(QSize(65, 65));
            }
        }
    }
}

//void Widget::print(int info) {
//    int fkclr = humanColor == WHITE ? 0 : 7;
//    for (int k = 0; k < 8; ++k) {
//        for (int g = 0; g < 8; ++g) {
//            if (board(g, k) != board.vacant()) {
//                buttons[fkclr - g][fkclr - k]->setIcon(QIcon("png/" + QString::number(board(g, k)->getName()) + QString::number(board(g, k)->getColor()) + ".png"));
//            } else {
//                buttons[fkclr - g][fkclr - k]->setIcon(QIcon());
//            }
//            buttons[fkclr - g][fkclr - k]->setIconSize(QSize(65, 65));
//        }
//    }
//    return;
//}

Widget::~Widget() {
    delete ui;
}

