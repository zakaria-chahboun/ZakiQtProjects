#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qtrpt.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// print report test : btn
void MainWindow::on_printR_clicked()
{
    QtRPT *report = new QtRPT(this);

    ui->printR->setText("");
}
