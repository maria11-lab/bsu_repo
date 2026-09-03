#ifndef FLIGHTCONTROLLER_H
#define FLIGHTCONTROLLER_H

#include "flightmodel.h"
#include <QObject>

class FlightController : public QObject {
    Q_OBJECT
private:
    FlightModel *m_model;

public:
    explicit FlightController(FlightModel *model, QObject *parent = nullptr);

    QString processSearchQuery(const QString &destination);
};

#endif // FLIGHTCONTROLLER_H