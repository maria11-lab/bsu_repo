#include <QApplication>
#include "tictactoe.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    int n = 3;
    if (argc > 1) {
        int val = atoi(argv[1]);
        if (val >= 3 && val <= 5) {
            n = val;
        } else if (val > 5) {
            n = 5;
        } else {
            n = 3;
        }
    }

    TicTacToe w(n);
    w.show();
    return a.exec();
}