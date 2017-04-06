#include "EventLabel.h"

EventLabel::EventLabel()
{

}

void EventLabel::mouseMoveEvent(QMouseEvent * event)
{
    this->setText(QString("<center><h1>Move: %1, %2</h1></center>").arg(QString::number(event->x()), QString::number(event->y())));
}

void EventLabel::mousePressEvent(QMouseEvent * event)
{
    this->setText(QString("<center><h1>Press: %1, %2</h1></center>").arg(QString::number(event->x()), QString::number(event->y())));
}

void EventLabel::mouseReleaseEvent(QMouseEvent * event)
{
    this->setText(QString("<center><h1>Release: %1, %2</h1></center>").arg(QString::number(event->x()), QString::number(event->y())));
}
