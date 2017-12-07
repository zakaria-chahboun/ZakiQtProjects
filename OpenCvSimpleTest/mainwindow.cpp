#include "mainwindow.h"
#include "ui_mainwindow.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
//~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <QTemporaryFile>

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

/* Show Image ^^ */
void MainWindow::on_pushButton_clicked()
{
    // Temp File Frome Resource ^^
    this->temp_image = QTemporaryFile::createNativeFile(":/image.jpg");
    if(!this->temp_image->open())
        return;
    QString img = this->temp_image->fileName();

    // read an image
    cv::Mat image = cv::imread(img.toStdString(), 1);
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", image);

    // Remove Temp File
    this->temp_image->close();
    this->temp_image->remove();
}
