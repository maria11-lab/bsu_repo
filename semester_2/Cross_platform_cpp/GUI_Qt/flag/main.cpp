#include <QApplication>
#include <QTabWidget>
#include "FlagWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTabWidget *tabs = new QTabWidget();
    tabs->addTab(new FlagWidget(Country::Bulgaria), "Болгария");
    tabs->addTab(new FlagWidget(Country::Denmark), "Дания");

    tabs->resize(800, 600);
    tabs->show();

    return a.exec();
}