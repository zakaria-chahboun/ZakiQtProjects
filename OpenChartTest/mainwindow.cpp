#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <openchart.h>
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Example */
    mychart = new OpenChart(this);
    QMap<QString,double> map;

    map["Zakaria"] = 7500.00;
    map["Sarra"] = 1200.00;
    map["Ali"] = 220.50;
    map["Mona"] = 640.24;
    map["Khadija"] = 1000.00;
    map["Said"] = 2000.00;

    mychart->setTitle("Fisr Example Charts by Zaki");
    //mychart->setTipo(OpenChart::Sectores_2D);

    // Add items to your chart object
    QMap<QString, double>::iterator i;
      for (i = map.begin(); i != map.end(); ++i){
          mychart->addItem(i.key(),i.value());
          //mychart->addItem(i.key(),i.value(),Qt::gray);
      }

    // Add your chart object to layout
    ui->gridLayout->addWidget(mychart);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mychart;
}
