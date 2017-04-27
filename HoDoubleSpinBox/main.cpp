#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    QWidget widget;
//    widget.setFixedSize(800, 600);
//    widget.show();

    return a.exec();
}
