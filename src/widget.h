#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "chessboard.h"

//#define BOTCOLOR BLACK
// #define HUMANCOLOR WHITE

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void print();
//    void print(int info);
    void colRowPrint();
    void startGame();

private:
    Ui::Widget *ui;
    startChessboard board;
    moveYT oneMove;
    bool moveCan = false;
    bool botWait = true;
    int8_t humanColor = 0;
    QPushButton *buttons[8][8];

private slots:
    void click();
    void startGameW();
    void startGameB();

    void on_Widget_customContextMenuRequested(const QPoint &pos);
};

#endif // WIDGET_H
