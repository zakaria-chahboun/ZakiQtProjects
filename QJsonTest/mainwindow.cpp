#include "mainwindow.h"
#include "ui_mainwindow.h"
//~~~~~~~~~~~~~~~~~~~~~~
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
//~~~~~~~~~~~~~~~~~~~~~~
#include <QFile>
#include <QHash>
#include <QList>
#include <QDebug>
#include <QByteArray>
#include <QFileDialog>
#include <QMessageBox>
#include <QHashIterator>
#include <QTreeWidgetItem>

#include <QScriptEngine>
#include <QScriptValue>


#define MSGBOX(title,msg) QMessageBox::information(this,title,msg)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);

    //* * * * * * * * * * * * * *
    QString script = "var str = '{\"a\":1,\"b\":2}';"
                     "var obj = JSON.parse(str);"
                     "obj";
    QScriptEngine myEngine;
    QScriptValue value = myEngine.evaluate(script);

    qDebug() << value.toVariant();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Open JSON File */
void MainWindow::on_openFile_clicked()
{
    /* Get Json File */
    auto filename = QFileDialog::getOpenFileName(this,"Open Json File","C:/Users/astrolabe main/Desktop",
                                                 tr("JSON Files (*.json *.bson)"));
    ui->showPath->setText(filename);

    QFile file(filename);

    /* Read Json File */
    auto isOpen = file.open(QIODevice::ReadOnly |QIODevice::Text);
    if(!isOpen){
        MSGBOX("Input Error","Connot Open File\n\n"+file.errorString());
        file.close();
        return;
    }
    QByteArray data = file.readAll();
    file.close(); // :)

    /* Read Json Data */
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
    QJsonObject jsonObject = jsonDoc.object();

    /* Check if JSON data is Correct format */
    if(jsonDoc.isNull()){
        MSGBOX("JSON Parse Error","Failed to create JSON doc!");
        return;
    }else if(!jsonDoc.isObject()){
        MSGBOX("JSON Object Error","JSON is not an object!");
        return;
    }else if(jsonObject.isEmpty()){
         MSGBOX("JSON Empty Object","JSON object is empty!");
         return;
    }


    /* Success Data :) */
    // My JSON Structers : "{[ {obj1},{obj2},{obj3}... ]}" */

    QHash<QString,QString> hash; // temp store
    QList<QHash<QString,QString>> EmList; // list store

    QJsonArray jsonArray = jsonObject["Emps"].toArray(); // data is a big Array :)

    for(const QJsonValue &value: jsonArray) {
        QJsonObject obj = value.toObject(); // every element is an object :)
        hash["id"] = QString::number(obj["id"].toInt());
        hash["fname"] = obj["fname"].toString();
        hash["lname"] = obj["lname"].toString();
        hash["age"] = QString::number(obj["age"].toInt());

        EmList << hash;
    }

    /* Display Data */
    for(const QHash<QString,QString> &myhash : EmList){
    QHashIterator<QString, QString> i(myhash);
      while (i.hasNext()) {
          i.next();
          qDebug() << i.key() << ": " << i.value();
      }
      ui->treeWidget->
      qDebug() << "----------------------";
    }
}
