#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QIntValidator>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableHistory->setColumnCount(2);
    ui->tableHistory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->lineInput->setValidator(new QIntValidator(0, 9999, this));
    ui->lineInput->setMaxLength(4);

    ui->lineInput->setEnabled(false);
    ui->btnCheck->setEnabled(false);
    attempts = 0;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::generateSecret() {
    secretCode = "";
    QList<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i = 0; i < 4; ++i) {
        int idx = QRandomGenerator::global()->bounded(digits.size());
        secretCode += QString::number(digits.takeAt(idx));
    }
}

void MainWindow::on_btnNewGame_clicked() {
    generateSecret();
    attempts = 0;
    ui->tableHistory->setRowCount(0);
    ui->lblStatus->setText("Игра началась!");
    ui->lineInput->clear();

    ui->lineInput->setEnabled(true);
    ui->btnCheck->setEnabled(true);
    ui->lineInput->setFocus();
}

void MainWindow::on_btnCheck_clicked() {
    QString guess = ui->lineInput->text().trimmed();

    bool isNum;
    guess.toInt(&isNum);
    if (guess.length() != 4 || !isNum) {
        QMessageBox::warning(this, "Ошибка", "Введите 4 цифры!");
        return;
    }

    attempts++;
    int bulls = 0;
    int cows = 0;

    for (int i = 0; i < 4; ++i) {
        if (guess.at(i) == secretCode.at(i)) {
            bulls++;
        } else if (secretCode.contains(guess.at(i))) {
            cows++;
        }
    }

    int row = ui->tableHistory->rowCount();
    ui->tableHistory->insertRow(row);
    ui->tableHistory->setItem(row, 0, new QTableWidgetItem(guess));
    ui->tableHistory->setItem(row, 1, new QTableWidgetItem(
                                          QString("Быков: %1; Коров: %2").arg(bulls).arg(cows)));

    if (bulls == 4) {
        ui->lblStatus->setText(QString("Победа за %1 попыток!").arg(attempts));

        ui->lineInput->setEnabled(false);
        ui->btnCheck->setEnabled(false);

        loadRecords();

        bool isInTop = (recordsList.size() < 5) || (attempts < recordsList.takeAt(qMin(4, (int)recordsList.size()-1)).attempts);

        loadRecords();

        if (recordsList.size() < 5 || attempts < recordsList.last().attempts || recordsList.isEmpty()) {
            QMessageBox::information(this, "Ого!", "Классная попытка! Ты вошел в топ-5, напиши свое имя.");

            bool ok;
            QString name = QInputDialog::getText(this, "Рекорд!", "Ваше имя:",
                                                 QLineEdit::Normal, "", &ok);
            if (ok && !name.isEmpty()) {
                saveRecord(name, attempts);
            }
        } else {
            QMessageBox::information(this, "Победа!", QString("Вы угадали число! Попыток: %1. К сожалению, этого мало для топа.").arg(attempts));
        }
    } else {
        ui->lblStatus->setText("Не угадали, еще попытка...");
    }

    ui->lineInput->clear();
    ui->lineInput->setFocus();
}

void MainWindow::on_btnRecords_clicked() {
    loadRecords();
    QString report = "Топ-5 рекордов:\n\n";
    for (int i = 0; i < std::min(5, (int)recordsList.size()); ++i) {
        report += QString("%1. %2 — %3 попыток\n").arg(i+1).arg(recordsList[i].name).arg(recordsList[i].attempts);
    }
    QMessageBox::information(this, "Рекорды", recordsList.isEmpty() ? "Список пуст" : report);
}

void MainWindow::saveRecord(QString name, int score) {
    QFile file("records.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << name << ":" << score << "\n";
        file.close();
    }
}

void MainWindow::loadRecords() {
    recordsList.clear();
    QFile file("records.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList p = line.split(":");
            if (p.size() == 2) recordsList.append({p[0], p[1].toInt()});
        }
        file.close();
    }
    std::sort(recordsList.begin(), recordsList.end(), [](const Record& a, const Record& b) {
        return a.attempts < b.attempts;
    });

    if(recordsList.size() > 5) {
        recordsList = recordsList.mid(0, 5);
    }
}