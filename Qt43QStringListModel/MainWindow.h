#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QStringListModel * model;
    QListView * listView;
    void insertData();
    void deleteData();
    void showData();
};

#endif // MAINWINDOW_H
