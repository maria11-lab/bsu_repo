#ifndef FLAGWIDGET_H
#define FLAGWIDGET_H

#include <QWidget>
#include <QPainter>

enum class Country { Bulgaria, Denmark };

class FlagWidget : public QWidget {
    Q_OBJECT
public:
    explicit FlagWidget(Country country, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Country m_country;
    void drawBulgaria(QPainter &painter, const QRectF &rect);
    void drawDenmark(QPainter &painter, const QRectF &rect);
};

#endif