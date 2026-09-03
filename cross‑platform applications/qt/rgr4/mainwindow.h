#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QAction>
#include "flightmodel.h"
#include "flightcontroller.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    FlightModel *m_model;
    FlightController *m_controller;
    QTableWidget *m_tableWidget;

    QAction *m_actOpen;
    QAction *m_actSave;
    QAction *m_actSaveAs;
    QAction *m_actClose;
    QAction *m_actExit;
    QAction *m_actRequest;
    QAction *m_actAbout;

    QAction *m_actAdd;
    QAction *m_actEdit;
    QAction *m_actDelete;

    void createActions();
    void createMenus();
    void createToolBars();
    void updateTableData();
    void updateUIState();
    bool checkUnsavedChanges();

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotOpen();
    void slotSave();
    void slotSaveAs();
    void slotClose();
    void slotExit();
    void slotRequest();
    void slotAbout();

    void slotAddFlight();
    void slotEditFlight();
    void slotDeleteFlight();
    void slotCustomContextMenu(const QPoint &pos);
};

#endif // MAINWINDOW_H