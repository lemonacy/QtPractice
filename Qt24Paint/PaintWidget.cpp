#include "PaintWidget.h"
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QSize>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1024, 768);
    setWindowTitle(tr("Paint Demo"));
}

PaintWidget::~PaintWidget()
{

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    qDebug() << "Default brush style" << painter.brush().style();

    painter.drawLine(QLine(QPoint(0, 0), QPoint(100, 100)));

    painter.setPen(Qt::red);
    painter.drawRect(QRect(QPoint(100, 10), QSize(100, 80)));

    painter.setPen(QPen(Qt::black, 4, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(QPoint(330, 60), 100, 50);

}
