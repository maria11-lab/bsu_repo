#include "requestdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

RequestDialog::RequestDialog(FlightController *controller, QWidget *parent)
    : QDialog(parent), m_controller(controller)
{
    setWindowTitle("Поиск рейсов по направлению...");
    resize(500, 350);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mainLayout->addWidget(new QLabel("Введите пункт назначения (город):", this));

    QHBoxLayout *searchLayout = new QHBoxLayout();
    m_inputDestination = new QLineEdit(this);
    m_inputDestination->setPlaceholderText("Например: Moscow");
    m_btnSearch = new QPushButton("Найти", this);

    searchLayout->addWidget(m_inputDestination);
    searchLayout->addWidget(m_btnSearch);
    mainLayout->addLayout(searchLayout);

    mainLayout->addWidget(new QLabel("Результаты поиска (Ответ Контроллера):", this));
    m_outputResult = new QTextEdit(this);
    m_outputResult->setReadOnly(true);
    mainLayout->addWidget(m_outputResult);

    connect(m_btnSearch, &QPushButton::clicked, this, &RequestDialog::onSearchTriggered);
    connect(m_inputDestination, &QLineEdit::returnPressed, this, &RequestDialog::onSearchTriggered);
}

void RequestDialog::onSearchTriggered() {
    QString city = m_inputDestination->text();
    // Отправляем данные контроллеру и выводим ответ во View
    QString resultText = m_controller->processSearchQuery(city);
    m_outputResult->setText(resultText);
}