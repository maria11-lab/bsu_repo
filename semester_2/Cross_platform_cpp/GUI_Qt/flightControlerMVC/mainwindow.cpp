#include "mainwindow.h"
#include "requestdialog.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QHeaderView>
#include <QCloseEvent>
#include <QInputDialog>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    m_model = new FlightModel();
    m_controller = new FlightController(m_model, this);

    resize(750, 480);
    setWindowTitle("РГР №4: Система управления рейсами (MVC)");

    m_tableWidget = new QTableWidget(this);
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels(QStringList() << "Рейс" << "Направление" << "Вылет" << "Прилет" << "Свободные места");
    m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this, &MainWindow::slotCustomContextMenu);

    setCentralWidget(m_tableWidget);

    createActions();
    createMenus();
    createToolBars();

    slotClose();
}

MainWindow::~MainWindow() {
    delete m_model;
}

void MainWindow::createActions() {
    m_actOpen = new QAction("&Open...", this);
    m_actOpen->setShortcut(QKeySequence("CTRL+O"));
    connect(m_actOpen, &QAction::triggered, this, &MainWindow::slotOpen);

    m_actSave = new QAction("&Save", this);
    m_actSave->setShortcut(QKeySequence("CTRL+S"));
    connect(m_actSave, &QAction::triggered, this, &MainWindow::slotSave);

    m_actSaveAs = new QAction("Save &as...", this);
    connect(m_actSaveAs, &QAction::triggered, this, &MainWindow::slotSaveAs);

    m_actClose = new QAction("&Close", this);
    m_actClose->setShortcut(QKeySequence("CTRL+W"));
    connect(m_actClose, &QAction::triggered, this, &MainWindow::slotClose);

    m_actExit = new QAction("&Exit", this);
    m_actExit->setShortcut(QKeySequence("ALT+X"));
    connect(m_actExit, &QAction::triggered, this, &MainWindow::slotExit);

    m_actRequest = new QAction("&Request...", this);
    connect(m_actRequest, &QAction::triggered, this, &MainWindow::slotRequest);

    m_actAbout = new QAction("&About...", this);
    connect(m_actAbout, &QAction::triggered, this, &MainWindow::slotAbout);

    m_actAdd = new QAction("Добавить рейс", this);
    connect(m_actAdd, &QAction::triggered, this, &MainWindow::slotAddFlight);

    m_actEdit = new QAction("Изменить рейс", this);
    connect(m_actEdit, &QAction::triggered, this, &MainWindow::slotEditFlight);

    m_actDelete = new QAction("Удалить выбранные", this);
    connect(m_actDelete, &QAction::triggered, this, &MainWindow::slotDeleteFlight);
}

void MainWindow::createMenus() {
    QMenu *pmnuFile = menuBar()->addMenu("&File");
    pmnuFile->addAction(m_actOpen);
    pmnuFile->addAction(m_actSave);
    pmnuFile->addAction(m_actSaveAs);
    pmnuFile->addAction(m_actClose);
    pmnuFile->addSeparator();
    pmnuFile->addAction(m_actExit);

    QMenu *pmnuShow = menuBar()->addMenu("&Show");
    pmnuShow->addAction(m_actRequest);

    QMenu *pmnuHelp = menuBar()->addMenu("&Help");
    pmnuHelp->addAction(m_actAbout);
}

void MainWindow::createToolBars() {
    QToolBar *pToolBar = addToolBar("Инструменты");
    pToolBar->addAction(m_actOpen);
    pToolBar->addAction(m_actSave);
    pToolBar->addSeparator();
    pToolBar->addAction(m_actAdd);
    pToolBar->addAction(m_actDelete);
    pToolBar->addSeparator();
    pToolBar->addAction(m_actRequest);
}

void MainWindow::updateTableData() {
    m_tableWidget->setRowCount(0);
    const auto& flights = m_model->getAllFlights();
    for (int i = 0; i < flights.size(); ++i) {
        m_tableWidget->insertRow(i);
        m_tableWidget->setItem(i, 0, new QTableWidgetItem(flights[i].flightNumber));
        m_tableWidget->setItem(i, 1, new QTableWidgetItem(flights[i].destination));
        m_tableWidget->setItem(i, 2, new QTableWidgetItem(flights[i].departureTime));
        m_tableWidget->setItem(i, 3, new QTableWidgetItem(flights[i].arrivalTime));
        m_tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(flights[i].freeSeats)));
    }
    updateUIState();
}

void MainWindow::updateUIState() {
    bool hasModel = !m_model->getCurrentFilePath().isEmpty();

    if (hasModel) {
        statusBar()->showMessage(QString::number(m_model->getAllFlights().size()));
    } else {
        statusBar()->showMessage("Выберите модель");
    }
}

bool MainWindow::checkUnsavedChanges() {
    if (m_model->isModified()) {
        auto ret = QMessageBox::warning(this, "Несохраненные изменения",
                                        "Модель была изменена. Сохранить текущие изменения?",
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (ret == QMessageBox::Yes) {
            slotSave();
            return true;
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

void MainWindow::slotOpen() {
    if (!checkUnsavedChanges()) return;

    QString filePath = QFileDialog::getOpenFileName(this, "Открыть модель рейсов", "", "Текстовые базы (*.txt);;Все файлы (*.*)");
    if (!filePath.isEmpty()) {
        if (m_model->loadFromFile(filePath)) {
            m_actSave->setEnabled(true);
            m_actSaveAs->setEnabled(true);
            m_actClose->setEnabled(true);
            m_actAdd->setEnabled(true);
            m_actEdit->setEnabled(true);
            m_actDelete->setEnabled(true);
            m_actRequest->setEnabled(true);

            updateTableData();
            setWindowTitle(QString("РГР №4: Паттерн MVC — %1").arg(filePath));
        } else {
            QMessageBox::critical(this, "Ошибка", "Ошибка чтения файла.");
        }
    }
}

void MainWindow::slotSave() {
    if (m_model->getCurrentFilePath().isEmpty()) {
        slotSaveAs();
    } else {
        m_model->saveToFile(m_model->getCurrentFilePath());
        statusBar()->showMessage("Изменения успешно сохранены.", 2000);
    }
}

void MainWindow::slotSaveAs() {
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить дубликат модели", "", "Текстовые базы (*.txt)");
    if (!filePath.isEmpty()) {
        if (m_model->saveToFile(filePath)) {
            setWindowTitle(QString("РГР №4: Паттерн MVC — %1").arg(filePath));
            updateUIState();
        }
    }
}

void MainWindow::slotClose() {
    if (!checkUnsavedChanges()) return;

    m_model->clear();
    m_tableWidget->setRowCount(0);

    m_actSave->setEnabled(false);
    m_actSaveAs->setEnabled(false);
    m_actClose->setEnabled(false);
    m_actAdd->setEnabled(false);
    m_actEdit->setEnabled(false);
    m_actDelete->setEnabled(false);
    m_actRequest->setEnabled(false);

    setWindowTitle("РГР №4: Паттерн MVC");
    updateUIState();
}

void MainWindow::slotExit() {
    close();
}

void MainWindow::slotRequest() {
    RequestDialog dlg(m_controller, this);
    dlg.exec();
}

void MainWindow::slotAbout() {
    QMessageBox::about(this, "О разработчике",
                       "ФИО: Ваша Фамилия И.О.\nГруппа: Ваша Группа\nНомер варианта: УСР №2 (Авиарейсы)");
}

void MainWindow::slotAddFlight() {
    bool ok1, ok2, ok3, ok4, ok5;
    QString num = QInputDialog::getText(this, "Добавление", "Номер рейса:", QLineEdit::Normal, "", &ok1);
    if (!ok1 || num.isEmpty()) return;
    QString dest = QInputDialog::getText(this, "Добавление", "Пункт назначения:", QLineEdit::Normal, "", &ok2);
    if (!ok2 || dest.isEmpty()) return;
    QString dep = QInputDialog::getText(this, "Добавление", "Время вылета (ЧЧ:ММ):", QLineEdit::Normal, "", &ok3);
    if (!ok3) return;
    QString arr = QInputDialog::getText(this, "Добавление", "Время прилета (ЧЧ:ММ):", QLineEdit::Normal, "", &ok4);
    if (!ok4) return;
    int seats = QInputDialog::getInt(this, "Добавление", "Свободные места:", 0, 0, 500, 1, &ok5);
    if (!ok5) return;

    m_model->addFlight({num, dest, dep, arr, seats});
    updateTableData();
}

void MainWindow::slotEditFlight() {
    int row = m_tableWidget->currentRow();
    if (row < 0) return;

    Flight current = m_model->getAllFlights()[row];
    bool ok1, ok2, ok3, ok4, ok5;

    QString num = QInputDialog::getText(this, "Редактирование", "Номер рейса:", QLineEdit::Normal, current.flightNumber, &ok1);
    if (!ok1) return;
    QString dest = QInputDialog::getText(this, "Редактирование", "Пункт назначения:", QLineEdit::Normal, current.destination, &ok2);
    if (!ok2) return;
    QString dep = QInputDialog::getText(this, "Редактирование", "Время вылета:", QLineEdit::Normal, current.departureTime, &ok3);
    if (!ok3) return;
    QString arr = QInputDialog::getText(this, "Редактирование", "Время прилета:", QLineEdit::Normal, current.arrivalTime, &ok4);
    if (!ok4) return;
    int seats = QInputDialog::getInt(this, "Редактирование", "Свободные места:", current.freeSeats, 0, 500, 1, &ok5);
    if (!ok5) return;

    m_model->updateFlight(row, {num, dest, dep, arr, seats});
    updateTableData();
}

void MainWindow::slotDeleteFlight() {
    QList<QTableWidgetSelectionRange> ranges = m_tableWidget->selectedRanges();
    if (ranges.isEmpty()) return;

    for (int r = m_tableWidget->rowCount() - 1; r >= 0; --r) {
        if (m_tableWidget->item(r, 0)->isSelected()) {
            m_model->removeFlight(r);
        }
    }
    updateTableData();
}

void MainWindow::slotCustomContextMenu(const QPoint &pos) {
    if (!m_actAdd->isEnabled()) return;

    QMenu menu(this);
    menu.addAction(m_actAdd);
    menu.addAction(m_actEdit);
    menu.addAction(m_actDelete);
    menu.exec(m_tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (checkUnsavedChanges()) {
        event->accept();
    } else {
        event->ignore();
    }
}