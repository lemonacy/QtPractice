#include "MainWindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) // 需要用QWidget来实现，如果用QMainWindow，下面的布局会有问题
    : QWidget(parent)
{
    QStringList data;
    data << "Letter A" << "Letter B" << "Letter C";
    model = new QStringListModel(this);
    model->setStringList(data);

    listView = new QListView(this);
    listView->setModel(model);
    listView->resize(200, 100);

    QHBoxLayout * hLayout = new QHBoxLayout();
    QPushButton * insertBtn = new QPushButton(tr("Insert"), this);
    connect(insertBtn, &QPushButton::clicked, this, &MainWindow::insertData);
    QPushButton * deleteBtn = new QPushButton(tr("Delete"), this);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteData);
    QPushButton * showBtn = new QPushButton(tr("Show"), this);
    connect(showBtn, &QPushButton::clicked, this, &MainWindow::showData);
    hLayout->addWidget(insertBtn);
    hLayout->addWidget(deleteBtn);
    hLayout->addWidget(showBtn);

    QVBoxLayout * vLayout = new QVBoxLayout(this);
    vLayout->addWidget(listView);
    vLayout->addLayout(hLayout);
    setLayout(vLayout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::insertData()
{
    bool bOK;
    QString text = QInputDialog::getText(this, "Insert", "Please input new data:", QLineEdit::Normal, "You are inserting new data.", &bOK);
    if (bOK)
    {
        int row = listView->currentIndex().row();
        model->insertRow(row);
        QModelIndex index = model->index(row);
        model->setData(index, text);
        listView->setCurrentIndex(index);
        listView->edit(index);
    }
}

void MainWindow::deleteData()
{
    if (model->rowCount() > 1)
        model->removeRows(listView->currentIndex().row(), 1);
}

void MainWindow::showData()
{
    QVariant val = model->data(listView->currentIndex(), Qt::DisplayRole);
    QMessageBox::information(this, "Data", val.toString());
}
