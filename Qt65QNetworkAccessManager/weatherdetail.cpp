#include "weatherdetail.h"

WeatherDetail::WeatherDetail()
{
    d = nullptr;
}

WeatherDetail::~WeatherDetail()
{
    if (d)
        delete d;
    d = nullptr;
}

QString WeatherDetail::desc()
{
    return d->desc;
}
void WeatherDetail::setDesc(const QString &desc)
{
    d->desc = desc;
}
QString WeatherDetail::icon()
{
    return d->icon;
}
void WeatherDetail::setIcon(const QString &icon)
{
    d->icon = icon;
}

class WeatherDetail::Private
{
public:
    QString desc;
    QString icon;
};

QDebug operator <<(QDebug dbg, const WeatherDetail &wd)
{
    dbg.nospace() << "("
                  << "Description: " << wd.desc() << ";"
                  << "Icon: " << wd.icon()
                  << ")";
    return dbg.space();
}
