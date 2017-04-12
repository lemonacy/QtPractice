#include "weatherinfo.h"

WeatherInfo::WeatherInfo()
{
    d = nullptr;
}

WeatherInfo::~WeatherInfo()
{
    if (d)
        delete d;
    d = nullptr;
}

QString WeatherInfo::cityName() const
{
    return d->cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    d->cityName = cityName;
}

quint32 WeatherInfo::id() const
{
    return d->id;
}

void WeatherInfo::setId(const quint32 id)
{
    d->id = id;
}

QDateTime WeatherInfo::dateTime() const
{
    return d->dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    d->dateTime = dateTime;
}

float WeatherInfo::temperature() const
{
    return d->temperature;
}

void WeatherInfo::setTemperature(const float temperature)
{
    d->temperature = temperature;
}

float WeatherInfo::humidity() const
{
    return d->humidity;
}

void WeatherInfo::setHumidity(const float humidity)
{
    d->humidity = humidity;
}

float WeatherInfo::pressure() const
{
    return d->pressure;
}

void WeatherInfo::setPressure(const float pressure)
{
    d->pressure = pressure;
}

QList<WeatherDetail *> WeatherInfo::details() const
{
    return d->details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    d->details = details;
}

class WeatherInfo::Private
{
public:
    QString cityName;
    quint32 id;
    QDateTime dateTime;
    float temperature;
    float humidity;
    float pressure;
    QList<WeatherDetail*> details;
};

QDebug operator <<(QDebug dbg, WeatherInfo &wi)
{
    dbg.nospace() << "("
                  << "City name: " << wi.cityName() << ";"
                  << "City id: " << wi.id() << ";"
                  << "Date time: " << wi.dateTime().toString(Qt::DefaultLocaleLongDate) << ";"
                  << "Temperature: " << wi.temperature() << ";"
                  << "Humidity: " << wi.humidity() << ";"
                  << "Pressure: " << wi.pressure() << ";" << std::endl
                  << "Details: [";
    foreach (WeatherDetail * detail, wi.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", Icon: " << detail->icon() << "),";
    }
    dbg.nospace() << "] )";

    return dbg.space();
}
