#ifndef FLIGHTMODEL_H
#define FLIGHTMODEL_H

#include <QString>
#include <QVector>

struct Flight {
    QString flightNumber;
    QString destination;
    QString departureTime;
    QString arrivalTime;
    int freeSeats;
};

class FlightModel {
private:
    QVector<Flight> m_flights;
    QString m_currentFilePath;
    bool m_isModified;

public:
    FlightModel();

    bool loadFromFile(const QString &filePath);
    bool saveToFile(const QString &filePath);

    const QVector<Flight>& getAllFlights() const { return m_flights; }
    void addFlight(const Flight &flight);
    void removeFlight(int index);
    void updateFlight(int index, const Flight &flight);
    void clear();

    QString getCurrentFilePath() const { return m_currentFilePath; }
    void setCurrentFilePath(const QString &path) { m_currentFilePath = path; }

    bool isModified() const { return m_isModified; }
    void setModified(bool modified) { m_isModified = modified; }

    QVector<Flight> findFlightsByDestination(const QString &city) const;
};

#endif // FLIGHTMODEL_H