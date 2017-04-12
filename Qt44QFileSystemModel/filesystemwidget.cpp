#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QHeaderView>
#include "filesystemwidget.h"

FileSystemWidget::FileSystemWidget(QWidget *parent)
    : QWidget(parent)
{
    m_model = new QFileSystemModel();
    m_model->setRootPath(QDir::currentPath());

    m_treeView = new QTreeView(this);
    m_treeView->header()->setStretchLastSection(false); // default false, but true for QTreeView
    m_treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    m_treeView->header()->setSortIndicatorShown(true);
#if QT_VERSION >= 0x050000
    m_treeView->header()->setSectionsClickable(true);
#else
    treeView->header()->setClickable(true);
#endif

    m_treeView->setModel(m_model);
    m_treeView->setRootIndex(m_model->index(QDir::currentPath()));


    QPushButton * mkdirBtn = new QPushButton(tr("Make Directory..."), this);
    QPushButton * rmBtn = new QPushButton(tr("Remove"), this);
    QHBoxLayout * btnLayout = new QHBoxLayout;
    btnLayout->addWidget(mkdirBtn);
    btnLayout->addWidget(rmBtn);

    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_treeView);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("File System Model"));

    connect(mkdirBtn, &QPushButton::clicked, this, &FileSystemWidget::mkdir);
    connect(rmBtn, &QPushButton::clicked, this, &FileSystemWidget::rm);
}

FileSystemWidget::~FileSystemWidget()
{

}

void FileSystemWidget::mkdir()
{
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid())
        return;
    QString dirName = QInputDialog::getText(this, tr("Create Directory"), tr("Directory Name"));
    if (dirName.isEmpty())
        return;
    QModelIndex newIndex = m_model->mkdir(index, dirName);
    if (!newIndex.isValid())
        QMessageBox::warning(this, tr("Create Directory"), tr("Failed to craete directory"));
}

void FileSystemWidget::rm()
{
    QModelIndex currIdx = m_treeView->currentIndex();
    if (!currIdx.isValid())
        return;
    bool ok = false;
    QFileInfo fileInfo = m_model->fileInfo(currIdx);
    if (fileInfo.isDir())
        ok = m_model->rmdir(currIdx);
    else
        ok = m_model->remove(currIdx);
    if (!ok)
        QMessageBox::warning(this, tr("Remove"), tr("Failed to remove %1").arg(m_model->fileName(currIdx)));
}
