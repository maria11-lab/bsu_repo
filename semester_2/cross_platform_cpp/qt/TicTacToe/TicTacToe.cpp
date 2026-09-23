#include "tictactoe.h"
#include "ui_tictactoe.h"
#include <QMessageBox>
#include <QRandomGenerator>

TicTacToe::TicTacToe(int n, QWidget *parent) : QWidget(parent), ui(new Ui::TicTacToe), N(n) {
    ui->setupUi(this);

    ui->modeComboBox->addItems({"Player vs Player", "Player vs CPU"});
    buttons.resize(N * N);

    for (int i = 0; i < N * N; ++i) {
        buttons[i] = new QPushButton("", this);
        buttons[i]->setFixedSize(60, 60);
        ui->gridLayout->addWidget(buttons[i], i / N, i % N);
        connect(buttons[i], &QPushButton::clicked, this, &TicTacToe::onButtonClick);
    }

    connect(ui->clearBtn, &QPushButton::clicked, this, &TicTacToe::resetBoard);
}

TicTacToe::~TicTacToe() {
    delete ui;
}

void TicTacToe::onButtonClick() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    int idx = buttons.indexOf(btn);

    if (!btn || !btn->text().isEmpty()) return;

    QString currentSign = isPlayer1Turn ? "X" : "O";
    processMove(idx, currentSign);

    if (ui->modeComboBox->currentIndex() == 1 && !isPlayer1Turn) {
        makeCPUMove();
    }
}

void TicTacToe::processMove(int index, QString sign) {
    buttons[index]->setText(sign);

    if (checkWinner(sign)) {
        QMessageBox::information(this, "Game Over", "Winner: " + sign);
        resetBoard();
        return;
    }

    bool hasEmpty = false;
    for (auto *btn : buttons) {
        if (btn->text().isEmpty()) {
            hasEmpty = true;
            break;
        }
    }

    if (!hasEmpty) {
        QMessageBox::information(this, "Game Over", "Draw!");
        resetBoard();
        return;
    }

    isPlayer1Turn = !isPlayer1Turn;
    ui->statusLabel->setText(isPlayer1Turn ? "Player1" : "Player2");
}

bool TicTacToe::checkWinner(QString sign) {
    for (int i = 0; i < N; ++i) {
        bool rowWin = true, colWin = true;
        for (int j = 0; j < N; ++j) {
            if (buttons[i * N + j]->text() != sign) rowWin = false;
            if (buttons[j * N + i]->text() != sign) colWin = false;
        }
        if (rowWin || colWin) return true;
    }

    bool diag1 = true, diag2 = true;
    for (int i = 0; i < N; ++i) {
        if (buttons[i * N + i]->text() != sign) diag1 = false;
        if (buttons[i * N + (N - 1 - i)]->text() != sign) diag2 = false;
    }
    return diag1 || diag2;
}

void TicTacToe::makeCPUMove() {
    int move = findBestMove("O");
    if (move == -1) move = findBestMove("X");

    if (move == -1 && buttons[4]->text().isEmpty()) {
        move = 4;
    }

    if (move == -1) {
        QVector<int> freeIndices;
        for (int i = 0; i < buttons.size(); ++i) {
            if (buttons[i]->text().isEmpty()) freeIndices.append(i);
        }
        if (!freeIndices.isEmpty()) {
            move = freeIndices[QRandomGenerator::global()->bounded(freeIndices.size())];
        }
    }

    if (move != -1) {
        processMove(move, "O");
    }
}

int TicTacToe::findBestMove(QString sign) {
    for (int i = 0; i < N; ++i) {
        int count = 0, emptyIdx = -1;
        for (int j = 0; j < N; ++j) {
            int idx = i * N + j;
            if (buttons[idx]->text() == sign) count++;
            else if (buttons[idx]->text().isEmpty()) emptyIdx = idx;
        }
        if (count == N - 1 && emptyIdx != -1) return emptyIdx;
    }

    for (int i = 0; i < N; ++i) {
        int count = 0, emptyIdx = -1;
        for (int j = 0; j < N; ++j) {
            int idx = j * N + i;
            if (buttons[idx]->text() == sign) count++;
            else if (buttons[idx]->text().isEmpty()) emptyIdx = idx;
        }
        if (count == N - 1 && emptyIdx != -1) return emptyIdx;
    }

    int countDiag1 = 0, emptyDiag1 = -1;
    for (int i = 0; i < N; ++i) {
        int idx = i * N + i;
        if (buttons[idx]->text() == sign) countDiag1++;
        else if (buttons[idx]->text().isEmpty()) emptyDiag1 = idx;
    }
    if (countDiag1 == N - 1 && emptyDiag1 != -1) return emptyDiag1;

    int countDiag2 = 0, emptyDiag2 = -1;
    for (int i = 0; i < N; ++i) {
        int idx = i * N + (N - 1 - i);
        if (buttons[idx]->text() == sign) countDiag2++;
        else if (buttons[idx]->text().isEmpty()) emptyDiag2 = idx;
    }
    if (countDiag2 == N - 1 && emptyDiag2 != -1) return emptyDiag2;

    return -1;
}

void TicTacToe::resetBoard() {
    for (auto *btn : buttons) btn->setText("");
    firstMoveStartsPlayer1 = !firstMoveStartsPlayer1;
    isPlayer1Turn = firstMoveStartsPlayer1;
    ui->statusLabel->setText(isPlayer1Turn ? "Player1" : "Player2");

    if (!isPlayer1Turn && ui->modeComboBox->currentIndex() == 1) {
        makeCPUMove();
    }
}