#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Record {
    QString name;
    int attempts;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnNewGame_clicked();
    void on_btnCheck_clicked();
    void on_btnRecords_clicked();

private:
    Ui::MainWindow *ui;
    QString secretCode;
    int attempts;
    QList<Record> recordsList;

    void generateSecret();
    void loadRecords();
    void saveRecord(QString name, int score);
};
#endif