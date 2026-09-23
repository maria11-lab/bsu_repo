#include "GraphWidget.h"
#include <QRandomGenerator>
#include <QPainter>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GraphWidget::updateBall);
    currentX = a;
    speed = 11;
    ballColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    setFocusPolicy(Qt::StrongFocus);
}

void GraphWidget::updateBall() {
    double step = 0.025 * direction;
    currentX += step;
    if (currentX >= b || currentX <= a) {
        direction *= -1;
        ballColor = QColor::fromRgb(QRandomGenerator::global()->generate());
    }
    update();
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(240, 240, 240));
    double minY = -1.1;
    double maxY = 1.1;
    auto toScreen = [&](double x, double y) {
        double px = (x - a) / (b - a) * width();
        double py = height() - (y - minY) / (maxY - minY) * height();
        return QPointF(px, py);
    };
    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    painter.drawLine(toScreen(a, 0), toScreen(b, 0));
    painter.drawLine(toScreen(0, minY), toScreen(0, maxY));
    painter.setPen(Qt::black);
    painter.drawText(toScreen(a, 0) + QPoint(5, -10), QString("a: %1").arg(a));
    painter.drawText(toScreen(b, 0) + QPoint(-45, -10), QString("b: %1").arg(b));
    painter.drawText(toScreen(0, 1) + QPoint(10, 5), "max: 1");
    painter.drawText(toScreen(0, -1) + QPoint(10, 5), "min: -1");

    painter.setBrush(Qt::black);
    double intersections[] = {-2 * M_PI, -M_PI, 0, M_PI, 2 * M_PI};
    for (double x : intersections) {
        if (x >= a && x <= b) {
            QPointF p = toScreen(x, 0);
            painter.setPen(Qt::black);
            painter.drawEllipse(p, 3, 3);
            painter.drawText(p + QPoint(5, 15), QString("(%1, 0)").arg(x, 0, 'f', 2));
        }
    }
    painter.setPen(QPen(Qt::blue, 2));
    for (double x = a; x < b; x += 0.05) {
        painter.drawLine(toScreen(x, f(x)), toScreen(x + 0.05, f(x + 0.05)));
    }
    if (isMoving) {
        int displaySpeed = 21 - speed;
        if (displaySpeed < 1) displaySpeed = 1;
        if (displaySpeed > 20) displaySpeed = 20;

        painter.setPen(Qt::black);
        painter.drawText(175, 30, QString("Скорость (1-20): %1").arg(displaySpeed));

        painter.setBrush(ballColor);
        painter.setPen(QPen(Qt::gray, 1));
        double ballDiam = width() * 0.015;
        painter.drawEllipse(toScreen(currentX, f(currentX)), ballDiam, ballDiam);
    }
}

void GraphWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMoving = true;
        currentX = a;
        direction = 1;
        ballColor = QColor::fromRgb(QRandomGenerator::global()->generate());
        timer->start(speed);
    }
}

void GraphWidget::keyPressEvent(QKeyEvent *event) {
    QString keyText = event->text().toLower();
    if (keyText == "s" || event->key() == Qt::Key_S || keyText == "ы") {
        timer->stop();
    } else if (keyText == "b" || event->key() == Qt::Key_B || keyText == "и") {
        timer->start(speed);
    } else if (event->text() == "+" || event->text() == "=") {
        if (speed > 1) {
            speed--;
            if (timer->isActive()) timer->start(speed);
        }
    } else if (event->text() == "-") {
        if (speed < 20) {
            speed++;
            if (timer->isActive()) timer->start(speed);
        }
    }
}