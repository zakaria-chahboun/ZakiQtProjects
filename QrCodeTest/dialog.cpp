#include "dialog.h"
#include "ui_dialog.h"
// Camera Capture :)
#include <QCamera> // drive
#include <QCameraInfo> // infos
#include <QFileDialog> // for save :)
#include <QCameraViewfinder> // for view
#include <QCameraImageCapture> // for capture and save file
#include <QImageEncoderSettings> // for set JPG or PNG ..

#include <QList>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QZXing.h> // QrDecode
#include <QMessageBox>
#include <QTemporaryFile> // image stored in file temporary

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    /* List for Avialbe Camera */
    this->listOfAvailableCameras();

    /* Camera inisializations */
    this->myCamera = new QCamera(this); // device : default camera used in system
    this->myCameraViewFinder = new QCameraViewfinder(this); // to show
    this->myCameraCapture = new QCameraImageCapture(this->myCamera,this); // to capture

    /* link Camera Devide with Object Show */
    this->myCamera->setViewfinder(this->myCameraViewFinder);
    /* Add Viewfider to the Form :) */
    ui->scrollArea->setWidget(myCameraViewFinder);
    /* Start Camera Show :) */
    if(this->myCamera->isAvailable())
        this->myCamera->start();

    // -------------- MY CONGIGURATIONS ----------------

    /* Camera is configured for still frames capture :) */
    this->myCamera->setCaptureMode(QCamera::CaptureStillImage);
    /* Config Capture for Save Image to Buffer (QImage) */
    this->myCameraCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    /* Signals & Slots "Capture" : Important for get image from %temp% to "QImage" Buffer */
    QObject::connect(this->myCameraCapture, &QCameraImageCapture::imageCaptured, [=] (int id, QImage img) {
        int w,h;
        w = img.width() / 6;
        h = img.height() / 6;
        // for Show (thumbnail)
        ui->labelQrCodeImage->setPixmap(QPixmap::fromImage(img.scaled(w,h)));
        // for Manupulate (with original size)
        this->myTmpImage = img;
        // run my function to decode :)
        this->decodeQrCode();
    });
}

/* Close Event :) */
void Dialog::closeEvent(QCloseEvent *e)
{
    this->parentWidget()->show();
    e->accept();
}

Dialog::~Dialog()
{
    delete ui;
    delete myCamera;
    delete myCameraCapture;
    delete myCameraViewFinder;

    /* Remove Temporary Image */
        /*
         * Because The QTempFile Create a file without extention
         * and when we capture image, it create a new file with (.JPG) exention
         * this is mean 'New Image' and when the program finish
         * the QTempFile destructor remove 'Temp File'
         * but not the new 'Image File' ok!
         * so we want to remove it with add '.JPG' extention :) ZAKI
         *
         * I added this operation in destructor scope, because 'New Image' stile opened
         * and we cannot remove it, so here is the solution ^^
    */
        QString location = this->MyTempFile.fileName()+".jpg";
        QFile file(location);
        file.remove();
}

/* on Camera Start */
void Dialog::on_btnStart_clicked()
{
    if(this->myCamera->isAvailable())
        this->myCamera->start();
}

/* on Camera Stop */
void Dialog::on_btnStop_clicked()
{
    if(this->myCamera->isAvailable())
        this->myCamera->stop();
}

/* Scanne QrCode Button : capture */
void Dialog::on_btnScanne_clicked()
{
    if(!this->myCamera->isAvailable())
        return;

    // Create a temorary file(image) for storing image
    QString tempImage;
    if(this->MyTempFile.open()) {
             tempImage = this->MyTempFile.fileName();// returns the unique file name
    }

    this->myCamera->searchAndLock();

    /* "capture()" do :
     * take iamage & stored in "tempImage" & run "imageCaptured" Signal :)
     * "imageCaptured" Signal containt my "decodeQrCode" function :)
    */
    this->myCameraCapture->capture(tempImage);
    this->myCamera->unlock();
}

/* My Global Function :) */
void Dialog::decodeQrCode(){

    /* Do not manupulate an empty image :) */
    if(this->myTmpImage.isNull()){
        ui->displayQrCodeText->setText("<p style='color:red;'>NO IMAGE HERE !</p>");
        return;
    }

    QZXing decoder;
    /* Set Barcode/Qrcode Types .. */
    decoder.setDecoder(QZXing::DecoderFormat_QR_CODE);

    QString result = decoder.decodeImage(this->myTmpImage);
        if(result.isEmpty())
            ui->displayQrCodeText->setText("<b style='color:gray;'>NULL</b>");
        else{
            ui->displayQrCodeText->setText("<b style='color:green;'>"+result.replace("\n","<br>")+"</b>");
        }
}

/* Public Function : get list of available cameras */
void Dialog::listOfAvailableCameras()
{
    // clear data
    ui->listCameras->clear();
    // add items
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      foreach (const QCameraInfo &cameraInfo, cameras)
           ui->listCameras->addItem(cameraInfo.description());
}

/* Update ComboBox List : click on btn */
void Dialog::on_toolButton_clicked()
{
    this->listOfAvailableCameras();
}

/* Chose Camera Frome ComboBox */
void Dialog::on_listCameras_activated(const QString &arg1)
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      foreach (const QCameraInfo &cameraInfo, cameras){
          if(cameraInfo.description() == arg1)
              this->myCamera = new QCamera(cameraInfo);
      }
}
