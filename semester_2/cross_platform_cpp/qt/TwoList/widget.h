#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
    void on_btnClear_clicked();

    void on_btnToRight_clicked();
    void on_btnToLeft_clicked();
    void on_btnSort_clicked();

    void on_checkMulti_toggled(bool checked);
    void on_checkIconMode_toggled(bool checked);

private:
    Ui::Widget *ui;
    void setupDefaultListSettings(QListWidget *list);
};
#endif // WIDGET_H