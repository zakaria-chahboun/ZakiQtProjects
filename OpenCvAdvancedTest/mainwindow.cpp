#include "mainwindow.h"
#include "ui_mainwindow.h"
//~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <CVImageWidget/cvimagewidget.h>
//~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <opencv2/objdetect/objdetect.hpp> // face detecting ..
#include <opencv2/imgproc/imgproc.hpp> // image processing
//~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#define MY_TEST(msg) QMessageBox::information(this,"Test",msg)


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Create the image widget
    this->imageWidget = new CVImageWidget(this);
    ui->verticalLayout->addWidget(imageWidget);

    // Load an image
    cv::Mat image = cv::imread("C:/image.jpg", true);
    this->imageWidget->showImage(image);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Start Camera : button */
void MainWindow::on_btnStartCamera_clicked()
{
    /* if no camera or cannot open */
    if(!this->mycap.isOpened())
        if(!this->mycap.open(0))
            return;

    this->MyTimerID = startTimer(0); // every milliseconds : call timerEvent(..)
}

/* timerEvent : override */
void MainWindow::timerEvent(QTimerEvent *event)
{
    bool isRead = this->mycap.read(this->myImgFrame); // read a new frame from video

    if (!isRead) //if not success
    {
         QMessageBox::critical(this,"EROOR","Cannot read the video frame");
         killTimer(this->MyTimerID);
    }

    this->myfaceDetect(this->runDetectFace);
    this->imageWidget->showImage(this->myImgFrame); // show in new own Widgets :D
}

/* My Global Funcrion : Face Detection */
void MainWindow::myfaceDetect(bool run)
{
    // Turn off if not checked : by checkbox
    if(!run){
        return;
    }

    // Load Face cascade (.xml file)
    std::string xml = "C:\\Qt\\OpenCV3.2.0vc14\\opencv\\sources\\data"
                      "\\haarcascades\\haarcascade_frontalface_alt2.xml";
    cv::CascadeClassifier face_cascade;
    face_cascade.load(xml);

    // Detect faces
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(this->myImgFrame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    // Draw circles on the detected faces
    for(int i = 0; i < faces.size(); i++)
    {
        cv::Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        cv::ellipse(this->myImgFrame, center, cv::Size(faces[i].width*0.5,
                    faces[i].height*0.5), 0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
}

/* Active Face Detect : checkbox */
void MainWindow::on_checkBoxFaceDetect_toggled(bool checked)
{
    this->runDetectFace = checked;
}
