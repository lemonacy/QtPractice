#ifndef WEATHERINFO_H
#define WEATHERINFO_H
#include <QObject>
#include <QDebug>
#include <QDateTime>
#include "weatherdetail.h"

class WeatherInfo
{
public:
    WeatherInfo();
    ~WeatherInfo();

    QString cityName() const;
    void setCityName(const QString &cityName);

    quint32 id() const;
    void setId(const quint32 id);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    float temperature() const;
    void setTemperature(const float temperature);

    float humidity() const;
    void setHumidity(const float humidity);

    float pressure() const;
    void setPressure(const float pressure);

    QList<WeatherDetail *> details() const;
    void setDetails(const QList<WeatherDetail*> details);

private:
    class Private;
    friend class Private;
    Private *d;
};

QDebug operator <<(QDebug dbg, WeatherInfo &wi);

#endif // WEATHERINFO_H
