#include "Widget.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QMenuBar>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("Enter your age"));

    QSpinBox * spin = new QSpinBox(this);
    spin->setRange(0, 130);
    QSlider * slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 130);

    //    connect(spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), slider, &QSlider::setValue); // static_cast<void (QSpinBox::*)(int)>()   way:1
    void (QSpinBox:: *fn)(int) = &QSpinBox::valueChanged;
    connect(spin, fn, slider, &QSlider::setValue);  // way:2
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);

    spin->setValue(33);

    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(spin);
    mainLayout->addWidget(slider);

    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setMenuBar(new QMenuBar(this));
    layout->addLayout(mainLayout);
    //    layout->addWidget(new QStatusBar(this));

    this->setLayout(layout);
}

Widget::~Widget()
{

}
