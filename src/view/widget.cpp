#include "widget.h"
#include "./ui_widget.h"
#include <stdlib.h>
#include <QString>
// #include <iostream>
#include <unistd.h>
#include <thread>
#include <QSplitter>



Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget), oneMove(0, 0, 0, 0), board(0) {
    ui->setupUi(this);
    for (int k = 0; k < 8; k++) {
        for (int g = 0; g < 8; g++) {
            if (ui->gridLayout_2->itemAtPosition(g, k)) {
                buttons[k][-g + 7] = dynamic_cast<QPushButton*>(ui->gridLayout_2->itemAtPosition(g, k)->widget());
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
}

void Widget::startGameW() {
    if (!botWait) return;
    humanColor = WHITE;
    board.newStart(BLACK, ui->spinBox->value());
    colRowPrint();
    this->print();
}

void Widget::startGameB() {
    if (!botWait) return;
    humanColor = BLACK;
    board.newStart(WHITE, ui->spinBox->value());
    colRowPrint();
    std::thread thr(&startChessboard::botMove<Widget>, &board, &botWait, this);
    thr.detach();
    this->print();
}

void Widget::colRowPrint() {
    if (humanColor == WHITE) {
        for (int g = 0; g < 8; g++) {
            dynamic_cast<QLabel*>(ui->verticalLayout->itemAt(7 - g)->widget())->setText(QString::number(1 + g));
            dynamic_cast<QLabel*>(ui->horizontalLayout_2->itemAt(g + 1)->widget())->setText(QString(char('A' + g)));
        }
    } else {
        for (int g = 0; g < 8; g++) {
            dynamic_cast<QLabel*>(ui->verticalLayout->itemAt(7 - g)->widget())->setText(QString::number(8 - g));
            dynamic_cast<QLabel*>(ui->horizontalLayout_2->itemAt(g + 1)->widget())->setText(QString(char(7 + 'A' - g)));
        }
    }
}

void Widget::click() {
    if (!botWait) return;
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
            std::thread thr(&startChessboard::botMove<Widget>, &board, &botWait, this);
            thr.detach();
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
                buttons[g][k]->setIconSize(QSize(55, 55));
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
                buttons[7 - g][7 - k]->setIconSize(QSize(55, 55));
            }
        }
    }
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_Widget_customContextMenuRequested(const QPoint &pos) {

}

