#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMainWindow>
#include <QLabel>

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateBall();

private:
    QTimer *timer;
    double a = -2 * M_PI;
    double b = 2 * M_PI;
    double currentX;
    int speed = 11;
    int direction = 1;
    bool isMoving = false;
    QColor ballColor;

    double f(double x) { return std::sin(x); }
    void updateUiSpeed();
};

#endif