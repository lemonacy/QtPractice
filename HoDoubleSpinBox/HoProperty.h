#ifndef HOPROPERTY_H
#define HOPROPERTY_H

#include <QObject>

class HoProperty : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ Name WRITE setname NOTIFY nameChanged)
public:
    explicit HoProperty(QObject *parent = 0);
    QString Name() const {return name;}
    void setname(const QString & name) {this->name = name;}

signals:
    void nameChanged();
public slots:

private:
    QString name;
};

#endif // HOPROPERTY_H
