#include "PaintWidget.h"
#include <QPainter>
#include <QLine>
#include <QPoint>
#include <QDebug>
#include <QPen>
#include <QBrush>
#include <QRect>
#include <QSize>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QPointF>
#include <QDebug>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    resize(1024, 768);
    setWindowTitle(tr("Paint Demo"));

    connect(this, &PaintWidget::done, [](QString param){ qDebug() << param; });
    emit done("test123");
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

    painter.setRenderHint(QPainter::Antialiasing);
    QLinearGradient linearGradient(450, 10, 600, 120);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(0.5, Qt::green);
    linearGradient.setColorAt(1.0, Qt::red);
    painter.setBrush(QBrush(linearGradient));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(525, 100), 80, 80);

    QConicalGradient conicalGradient(QPointF(0, 0), 0);
    conicalGradient.setColorAt(0, Qt::red);
    conicalGradient.setColorAt(60.0/360.0, Qt::yellow);
    conicalGradient.setColorAt(120.0/360.0, Qt::green);
    conicalGradient.setColorAt(180.0/360.0, Qt::cyan);
    conicalGradient.setColorAt(240.0/360.0, Qt::blue);
    conicalGradient.setColorAt(300.0/360.0, Qt::magenta);
    conicalGradient.setColorAt(1.0, Qt::red);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(conicalGradient));
    painter.translate(800, 120);
    painter.drawEllipse(QPoint(0, 0), 100, 100);


}
