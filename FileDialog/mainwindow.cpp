#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionOpen->setStatusTip(tr("Open an existing file"));
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setStatusTip(tr("Save a new file"));
    m_textEdit = new QTextEdit(this);
    setCentralWidget(m_textEdit);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("Text files(*.txt);;Header files(*.h)"));
    if (path.isEmpty())
    {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file"));
        return;
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Read File"), tr("Can't open file:\n%1").arg(path));
        return;
    }
    QTextStream in(&file);
    m_textEdit->setText(in.readAll());
    file.close();
}
void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Open file"), ".", tr("Text files(*.txt)"));
    if (path.isEmpty())
    {
        QMessageBox::warning(this, tr("Path"), tr("Please choose a location to save file"));
        return;
    }
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, tr("Save File"), tr("Can't write to file:\n%1").arg(path));
        return;
    }
    QTextStream out(&file);
    out << m_textEdit->toPlainText();
    file.close();
}
