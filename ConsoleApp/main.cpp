#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QtCore>
#include "Observer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NewsPaper newspaper("Today is Fri");
    Reader reader;
    QObject::connect(&newspaper, &NewsPaper::newpaper, &reader, &Reader::receiveNewpaper);
    newspaper.send();

    qApp->dumpObjectTree();
    newspaper.dumpObjectInfo();

    return a.exec();
}
