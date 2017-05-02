#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    void paintEvent(QPaintEvent *event);

signals:
    void done(const QString param);

private slots:

};

#endif // PAINTWIDGET_H
