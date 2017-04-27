#include "MainWindow.h"
#include <QMessageBox>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    m_openAction->setShortcut(QKeySequence::Open);
    m_openAction->setStatusTip("open an existing file");
    QObject::connect(m_openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(m_openAction);
    fileMenu->addMenu("Recent Files");

    QToolBar * toolbar = addToolBar(tr("&File"));
    toolbar->addAction(m_openAction);

    statusBar();
}

MainWindow::~MainWindow()
{
    //    delete m_openAction;
}

void MainWindow::open()
{
    QDialog *dailog = new QDialog(this);
    dailog->setWindowTitle(tr("Hello, dialog"));
    dailog->setAttribute(Qt::WA_DeleteOnClose);
    dailog->exec();
}
