#ifndef WEATHERDETAIL_H
#define WEATHERDETAIL_H
#include <QObject>
#include <QDebug>

class WeatherDetail
{
public:
    WeatherDetail();
    ~WeatherDetail();

    QString desc() const;
    void setDesc(const QString &desc);
    QString icon() const;
    void setIcon(const QString &icon);

private:
    class Private;
    friend class Private;
    Private *d;
};

QDebug operator <<(QDebug dbg, const WeatherDetail &wd);

#endif // WEATHERDETAIL_H
