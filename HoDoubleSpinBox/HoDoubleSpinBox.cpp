#include "HoDoubleSpinBox.h"
#include <QLineEdit>
#include <QEvent>
#include <QDebug>
#include <QDateTime>
#include <QLineEdit>
#include <QMouseEvent>
#include <QStyle>
#include <QStyleOptionSpinBox>

HoDoubleSpinBox::HoDoubleSpinBox(QWidget *parent) : QDoubleSpinBox(parent)
{
    installEventFilter(this);
    setSingleStep(100);
    setRange(-40, 150);
    setValue(0);
    setMouseTracking(true);

    //lineEdit()->installEventFilter(this);
}

void HoDoubleSpinBox::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "Spin Box mousePressEvent";
    QDoubleSpinBox::mousePressEvent(event);
}

bool HoDoubleSpinBox::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent;
    QContextMenuEvent *contextMenuEvent;
    QStyleOptionSpinBox opt;
    QRect rect;
    QPoint mousePos;

    switch (event->type()) { // Even setMouseTracking(true); called, the mouse movement event not on spinbox, can't receive.
    case QEvent::MouseMove:
        qDebug() << "mouse move in eventFilter2" << QDateTime::currentDateTime().toString();
        break;
    }

    if (watched == this)
    {
        switch (event->type()) {
        case QEvent::MouseMove:
            qDebug() << "mouse move in eventFilter" << QDateTime::currentDateTime().toString();
            break;
        case QEvent::MouseButtonPress:
            mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() == Qt::LeftButton)
            {
                this->initStyleOption(&opt);
                mousePos = mouseEvent->pos();
                rect = this->style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxUp);
                if(rect.contains(mousePos))
                    qDebug() << "UP";
                rect = this->style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxDown);
                if(rect.contains(mousePos))
                    qDebug() << "DOWN";
            }
            break;
        case QEvent::ContextMenu:
            contextMenuEvent = static_cast<QContextMenuEvent*>(event);
            this->initStyleOption(&opt);
            mousePos = contextMenuEvent->pos();
            rect = this->style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxUp);
            if(rect.contains(mousePos))
            {
                qDebug() << "UP";
                return true;
            }

            rect = this->style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxDown);
            if (rect.contains(mousePos))
            {
                qDebug() << "DOWN";
                return true;
            }

            return false;
        default:
            break;
        }
    }
    else if (watched == lineEdit())
    {
        switch(event->type()) {
        case QEvent::ContextMenu:
            qDebug() << "right mouse clicked in lineedit";
            return false;
        }
    }
    return QDoubleSpinBox::eventFilter(watched, event);
}
