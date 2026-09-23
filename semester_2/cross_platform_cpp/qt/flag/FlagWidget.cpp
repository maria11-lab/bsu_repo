#include "FlagWidget.h"

FlagWidget::FlagWidget(Country country, QWidget *parent)
    : QWidget(parent), m_country(country) {}

void FlagWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), QColor(240, 240, 240));

    double aspect;
    if (m_country == Country::Bulgaria) aspect = 5.0 / 3.0;
    else aspect = 37.0 / 28.0;

    double w = width();
    double h = height();
    double canvasAspect = w / h;

    QRectF flagRect;
    if (canvasAspect > aspect) {
        double flagW = h * aspect;
        flagRect = QRectF((w - flagW) / 2.0, 0, flagW, h);
    } else {
        double flagH = w / aspect;
        flagRect = QRectF(0, (h - flagH) / 2.0, w, flagH);
    }

    if (m_country == Country::Bulgaria) drawBulgaria(painter, flagRect);
    else drawDenmark(painter, flagRect);
}

void FlagWidget::drawBulgaria(QPainter &painter, const QRectF &rect) {
    double stripeH = rect.height() / 3.0;
    painter.setPen(Qt::NoPen);

    painter.setBrush(Qt::white);
    painter.drawRect(QRectF(rect.x(), rect.y(), rect.width(), stripeH));

    painter.setBrush(QColor(0, 150, 110));
    painter.drawRect(QRectF(rect.x(), rect.y() + stripeH, rect.width(), stripeH));

    painter.setBrush(QColor(214, 38, 18));
    painter.drawRect(QRectF(rect.x(), rect.y() + 2 * stripeH, rect.width(), stripeH));
}

void FlagWidget::drawDenmark(QPainter &painter, const QRectF &rect) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(200, 16, 46));
    painter.drawRect(rect);

    double stripe = rect.height() * (4.0 / 28.0);
    double Pos = rect.height() * (12.0 / 28.0);

    painter.setBrush(Qt::white);
    painter.drawRect(QRectF(rect.x(), rect.y() + Pos, rect.width(), stripe));
    painter.drawRect(QRectF(rect.x() + Pos, rect.y(), stripe, rect.height()));
}