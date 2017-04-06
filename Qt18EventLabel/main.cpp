#include <QApplication>
#include "EventLabel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EventLabel eventLabel;
    eventLabel.setWindowTitle("Event Label");
    eventLabel.resize(300, 200);
    eventLabel.setMouseTracking(true);
    eventLabel.show();

    return a.exec();
}
