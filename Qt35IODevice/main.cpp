#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QIODevice>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qDebug() << "pwd " << QDir::currentPath();

    // Read file
    QFile file(".bashrc");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "open file failed";
    else
        while(!file.atEnd())
            qDebug() << file.readLine();

    QFileInfo info(file);
    qDebug() << info.isDir();
    qDebug() << info.isExecutable();
    qDebug() << info.baseName();
    qDebug() << info.completeBaseName();
    qDebug() << info.suffix();
    qDebug() << info.completeSuffix();

    // Manipulate binary file
    QFile datfd("the_universal_answer.dat");
    datfd.open(QIODevice::WriteOnly);
    QDataStream out(&datfd);
    out << QString("the answer is");
    out << (qint32)42;
    datfd.flush();
    datfd.close();

    datfd.open(QIODevice::ReadOnly);
    QDataStream in(&datfd);
    QString str;
    qint32 n;
    in >> str >> n;
    qDebug() << str << ": " << n;
    datfd.close();

    // seek
    datfd.open(QIODevice::ReadWrite);
    QDataStream stream(&datfd);
    stream << QString("the answer is中文");
    stream << (qint8)42;
    datfd.flush();
    QString outstr;
    out >> outstr;
    qDebug() << "outstr:" << outstr;
    out.device()->seek(0);
    out >> outstr;
    qDebug() << "outstr:" << outstr;
    datfd.close();

    // text stream & stream manipulators
    QFile txtfd("the_universal_answer.txt");
    if (txtfd.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QTextStream os(&txtfd);
        os.setCodec("UTF-16"); // default utf-8
        os << "The answer is " << bin << 42 << endl;
        os << showbase << uppercasedigits << hex << 12345678;
        txtfd.flush();
        txtfd.close();
    }

    return app.exec();
}
