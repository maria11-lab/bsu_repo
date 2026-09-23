#ifndef REQUESTDIALOG_H
#define REQUESTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include "flightcontroller.h"

class RequestDialog : public QDialog {
    Q_OBJECT
private:
    FlightController *m_controller;
    QLineEdit *m_inputDestination;
    QTextEdit *m_outputResult;
    QPushButton *m_btnSearch;

private slots:
    void onSearchTriggered();

public:
    RequestDialog(FlightController *controller, QWidget *parent = nullptr);
};

#endif // REQUESTDIALOG_H