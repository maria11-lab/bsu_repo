#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include <QPushButton>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class TicTacToe; }
QT_END_NAMESPACE

class TicTacToe : public QWidget {
    Q_OBJECT
public:
    TicTacToe(int n, QWidget *parent = nullptr);
    ~TicTacToe();

private slots:
    void onButtonClick();
    void resetBoard();

private:
    Ui::TicTacToe *ui;
    int N;
    bool isPlayer1Turn = true;
    bool firstMoveStartsPlayer1 = true;
    QVector<QPushButton*> buttons;

    void processMove(int index, QString sign);
    bool checkWinner(QString sign);
    void makeCPUMove();
    int findBestMove(QString sign);
};

#endif