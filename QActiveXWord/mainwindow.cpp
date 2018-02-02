#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAxObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Word App */
    QAxObject * appWord = new QAxObject("Word.Application");
    QAxObject * doc = appWord->querySubObject("Documents");
    doc = doc->querySubObject("Add()");

    QAxObject * range = doc->querySubObject("Range()");
    range->dynamicCall("SetRange(int,int)",0,100);
    range->setProperty("Text","Test One Zaki!");

    appWord->setProperty("Visible",true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
