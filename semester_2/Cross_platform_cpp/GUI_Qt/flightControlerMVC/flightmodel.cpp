#include "flightmodel.h"
#include <QFile>
#include <QTextStream>

FlightModel::FlightModel() : m_currentFilePath(""), m_isModified(false) {}

bool FlightModel::loadFromFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    m_flights.clear();
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(';');
        if (parts.size() == 5) {
            Flight f;
            f.flightNumber = parts[0].trimmed();
            f.destination = parts[1].trimmed();
            f.departureTime = parts[2].trimmed();
            f.arrivalTime = parts[3].trimmed();
            f.freeSeats = parts[4].toInt();
            m_flights.append(f);
        }
    }
    file.close();
    m_currentFilePath = filePath;
    m_isModified = false;
    return true;
}

bool FlightModel::saveToFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;

    QTextStream out(&file);
    for (const auto &f : m_flights) {
        out << f.flightNumber << ";"
            << f.destination << ";"
            << f.departureTime << ";"
            << f.arrivalTime << ";"
            << f.freeSeats << "\n";
    }
    file.close();
    m_currentFilePath = filePath;
    m_isModified = false;
    return true;
}

void FlightModel::addFlight(const Flight &flight) {
    m_flights.append(flight);
    m_isModified = true;
}

void FlightModel::removeFlight(int index) {
    if (index >= 0 && index < m_flights.size()) {
        m_flights.removeAt(index);
        m_isModified = true;
    }
}

void FlightModel::updateFlight(int index, const Flight &flight) {
    if (index >= 0 && index < m_flights.size()) {
        m_flights[index] = flight;
        m_isModified = true;
    }
}

void FlightModel::clear() {
    m_flights.clear();
    m_currentFilePath.clear();
    m_isModified = false;
}

QVector<Flight> FlightModel::findFlightsByDestination(const QString &city) const {
    QVector<Flight> result;
    QString searchCity = city.trimmed().toLower();
    for (const auto &f : m_flights) {
        if (f.destination.toLower() == searchCity) {
            result.append(f);
        }
    }
    return result;
}