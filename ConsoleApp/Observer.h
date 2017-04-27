#ifndef OBSERVER_H
#define OBSERVER_H
#include <QObject>
#include <QDebug>
#include <QtCore>

class NewsPaper : public QObject
{
    Q_OBJECT
public:
    NewsPaper(const QString &name, QObject * parent = Q_NULLPTR)
        :QObject(parent),
          m_name(name)
    {

    }

    void send()
    {
        emit newpaper(m_name);
    }

signals:
    void newpaper(const QString &name);

private:
    QString m_name;
};

class Reader : public QObject
{
    Q_OBJECT
public:
    Reader(){}

public slots:
    void receiveNewpaper(const QString &name)
    {
        qDebug() << "received newspaper " << name;
    }
};

#endif // OBSERVER_H
