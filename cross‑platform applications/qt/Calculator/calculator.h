#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QString>
#include <QStack>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class RPNCalculator {
public:
    double calculate(QString expression);
private:
    int getPriority(QString op);
    QStringList tokenize(QString exp);
    void processOperator(QStack<double>& values, QStack<QString>& ops);
};

class Calculator : public QWidget {
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void on_button_clicked();
    void on_PushButton_AC_clicked();
    void on_pushButton_Del_clicked();
    void on_pushButton_PM_clicked();
    void on_pushButton_Pr_clicked();
    void on_pushButton_Equal_clicked();

private:
    Ui::Calculator *ui;
};

#endif