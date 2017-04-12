#include "MainWindow.h"
#include "HoDoubleSpinBox.h"
#include "HoProperty.h"
#include <QWidget>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800, 600);
    QWidget * widget = new QWidget(this);
    HoDoubleSpinBox * spin = new HoDoubleSpinBox(widget);

    HoProperty pro;
    pro.setProperty("name", "Asran");
    qDebug() << pro.property("name").toString();


    QString json("{"
            "\"encoding\" : \"UTF-8\","
            "\"plug-ins\" : ["
            "\"python\","
            "\"c++\","
            "\"ruby\""
            "],"
            "\"indent\" : { \"length\" : 3, \"use_space\" : true }"
            "}");
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8(), &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (jsonDoc.isObject())
        {
            QVariantMap result = jsonDoc.toVariant().toMap();
            qDebug() << "encoding: " << result["encoding"].toString();
            qDebug() << "plugins:";
            foreach (QVariant plugin, result["plug-ins"].toList()) {
                qDebug() << "\t-" << plugin.toString();
            }
            QVariantMap indent = result["indent"].toMap();
            qDebug() << "length: " << indent["length"].toInt();
            qDebug() << "use_space:" << indent["use_space"].toBool();
        }
    }
    else
    {
        qFatal(error.errorString().toUtf8().constData());
        exit(1);
    }

    QVariantList people;
    QVariantMap bob;
    bob.insert("Name", "Bob");
    bob.insert("PhoneNumber", 13800);
    QVariantMap alice;
    alice.insert("Name", "Alice");
    alice.insert("PhoneNumber", 17100);
    people << bob << alice;

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(people);
    if (!jsonDocument.isNull())
    {
        qDebug() << QString(jsonDocument.toJson(QJsonDocument::Compact));
    }
}

MainWindow::~MainWindow()
{

}
