#include "flightcontroller.h"
#include "flightmodel.h"

FlightController::FlightController(FlightModel *model, QObject *parent)
    : QObject(parent), m_model(model) {}

QString FlightController::processSearchQuery(const QString &destination) {
    if (destination.trimmed().isEmpty()) {
        return "Ошибка: Строка поиска не должна быть пустой.";
    }

    QVector<Flight> results = m_model->findFlightsByDestination(destination);
    if (results.isEmpty()) {
        return QString("Рейсы в направлении \"%1\" не найдены.").arg(destination);
    }

    QString response = QString("Найдено рейсов: %1\n").arg(results.size());
    response += "--------------------------------------------------\n";
    for (const auto &f : results) {
        response += QString("Рейс: %1 | Вылет: %2 | Прилет: %3 | Свободных мест: %4\n")
                        .arg(f.flightNumber, 8)
                        .arg(f.departureTime)
                        .arg(f.arrivalTime)
                        .arg(f.freeSeats);
    }
    return response;
}