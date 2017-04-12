#ifndef HODOUBLESPINBOX_H
#define HODOUBLESPINBOX_H

#include <QDoubleSpinBox>

class HoDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT
public:
    explicit HoDoubleSpinBox(QWidget *parent = 0);

signals:

public slots:

private:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // HODOUBLESPINBOX_H
