#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>

class FileSystemWidget : public QWidget
{
    Q_OBJECT

public:
    FileSystemWidget(QWidget *parent = 0);
    ~FileSystemWidget();
private:
    QFileSystemModel * m_model;
    QTreeView * m_treeView;
private slots:
    void mkdir();
    void rm();
};

#endif // FILESYSTEMWIDGET_H
