#include "HoDoubleSpinBox.h"
#include <QLineEdit>
#include <QEvent>
#include <QDebug>

HoDoubleSpinBox::HoDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    lineEdit()->installEventFilter(this);
}

bool HoDoubleSpinBox::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
        break;
    default:
        break;
    }
    return false;
}
