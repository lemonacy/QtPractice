#include "MainWindow.h"
#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLocale local(QLocale(QLocale::French, QLocale::France));
    QLocale::setDefault(local);

    MainWindow w;
    w.show();

    return a.exec();
}
