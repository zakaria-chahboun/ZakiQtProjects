#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QSlider>
#include <QPixmap>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QSvgRenderer>
#include <QDialogButtonBox>
#include <QActionGroup>
// QrCode Generator/Scanner :)
#include <QZXing.h>
#include <QrCodeGenerator/QrCode.hpp>

using namespace qrcodegen; // NameSpace of QrCode Generator

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(250,400);

    /* Actions : Menu : For Check one option at time */
    /* Options : Low,Medium,Quartile or High */
    QActionGroup *myActionGroup = new QActionGroup(this);
    ui->actionLow->setActionGroup(myActionGroup);
    ui->actionMedium->setActionGroup(myActionGroup);
    ui->actionQuartile->setActionGroup(myActionGroup);
    ui->actionHigh->setActionGroup(myActionGroup);
    ui->actionLow->setChecked(true); // Low By Default :)

    /* Document Text : by defalut */
    this->docTextSave = "Zakaria\nChahboun\n21/03/1996\nComputer Science";

    /* Get Setting Saved From File :) */
    this->getSettingFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myDialog;
}

/* Generate QrCode Simple Text Button */
void MainWindow::on_pushButton_clicked()
{
    this->setQrCode(ui->lineEdit->text());
}

/* Generate QrCode Document Action (Menu) */
void MainWindow::on_actionWrite_Document_triggered()
{
    bool ok;
    QString text = QInputDialog::getMultiLineText(this,tr("Document"),tr("Write Your Text:"),
                                                this->docTextSave,&ok);

    if (ok && !text.isEmpty()){
        this->setQrCode(text);
        this->docTextSave = text;
    }
}

/* Save Image Button  */
void MainWindow::on_pushButton_2_clicked()
{
    /* Save Image As JPG or PNG .. */
    auto myImage = ui->label->pixmap();
    if(myImage == 0){
        QMessageBox::critical(this,"No Image","Cannot Save an Empty Image!");
        return;
    }

    QString fName = QFileDialog::getSaveFileName(this, tr("Save Image"),
                                 this->fileNameJPG,
                                 tr("Images (*.jpg *.png *.bmp)"));
    myImage->save(fName);
}

//*** My Public Function ***
void MainWindow::setQrCode(const QString mytext){

    /* Get Text From User */
    QByteArray text = mytext.toLatin1();
    /* Generate QR Code : With Error Corection Level :) */
    QrCode::Ecc level = QrCode::Ecc::LOW; // low by default ^^
    Level_QrCode saveLevel;
    bool L = ui->actionLow->isChecked();
    bool M = ui->actionMedium->isChecked();
    bool Q = ui->actionQuartile->isChecked();
    bool H = ui->actionHigh->isChecked();
    if(L) {level = QrCode::Ecc::LOW; saveLevel = Level_QrCode::LOW;}
    if(M) {level = QrCode::Ecc::MEDIUM; saveLevel = Level_QrCode::MEDIUM;}
    if(Q) {level = QrCode::Ecc::QUARTILE; saveLevel = Level_QrCode::QUARTILE;}
    if(H) {level = QrCode::Ecc::HIGH; saveLevel = Level_QrCode::HIGH;}
    QrCode qr = QrCode::encodeText(text.data(), level);

    /* Get SVG text code */
    QString svg;
    std::string cc = qr.toSvgString(2); // border = 2 or any :)
    svg = QString::fromStdString(cc);

    /* Save File Name Into Variable */
    this->fileNameJPG = "QR_CODE_" + QString(text).toUpper() + ".jpg";

    /* Render SVG code and check if valid or not */
    QSvgRenderer renderer;
    renderer.load(svg.toLatin1());
    bool renderValid = renderer.isValid();

    if(!renderValid){
        QMessageBox::critical(this,"SVG Render Error","Cannot renderd SVG code!");
        return;
    }

    /* Create Pixmap from SVG */
    QPixmap myImg(this->imageSize); // Size :)
    QPainter painter(&myImg);
    renderer.render(&painter, myImg.rect());

    /* and show it :) */
    ui->label->setPixmap(myImg);

    /* Save Options in File */
    this->saveSettingToFile(saveLevel,this->imageSize);

    /*
     ** Other Method To Save JPG Iamge From QImage **

        QImage img = QIcon(newPath).pixmap(QSize(200,200)).toImage();
        img.save(fileNameJPG);
    */
}

/* QrCode Scanner Action (Menu) */
void MainWindow::on_actionScanne_Code_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
          tr("Open Image"), "", tr("Image Files (*.jpg *.png *.bmp)"));

    if(filename.isEmpty())
        return;

    QImage imageToDecode(filename);
    QZXing decoder;
    /* Set Barcode/Qrcode Types .. */
    decoder.setDecoder(QZXing::DecoderFormat_QR_CODE);
    QString result = decoder.decodeImage(imageToDecode);

    if(result.isEmpty())
        result = "cannot find code!";

    QMessageBox::information(this,"QR Code",result);
}

//*** About Creator ***
void MainWindow::on_actioncreator_triggered()
{
    QMessageBox::about(this,"About Creator","This Application is Created by"
                       "<b> Zakaria Chahboun </b><br>"
                       "This is the version <b>1.0</b><br>"
                       "Generate at <b>28/11/2017</b><br><br>"
                       "<img src=':/Account Zaki.png'/><br><br>"
                       "Phone: +212 678807280<br><br>"
                       "Licence : This application is <b style='color:#24921f;font-size:12pt'>Free</b>"
                       "<b style='color:#fe2e62;font-size:12pt'>♥</b> to use<br>"
                       "<img src=':/QrcodeZakiCorporationLogo.png'/>");
}

/* Show other Dialog for Camera Show */
void MainWindow::on_actionCamera_Scanne_triggered()
{
    this->myDialog = new Dialog(this);
    this->myDialog->setModal(true);
    this->myDialog->show();
    this->hide();
}


/* ******** Options ******** */
// Help : action
void MainWindow::on_actionHelp_triggered()
{
    QString html =
            "Percentage of codewords can be restored .<br><br>"
            "Level <b style='color:#208eca'>(Low) 7%</b> restored.<br>"
            "Level <b style='color:#208eca'>(Medium) 15%</b> restored.<br>"
            "Level <b style='color:#208eca'>(Quartile) 25%</b> restored.<br>"
            "Level <b style='color:#208eca'>(High) 30%</b> restored.<br><br>"
            "Visit:<br>"
            "<span style='color:green'>https://en.wikipedia.org/wiki/QR_code</span>"
            "<span style='color:gray'>#Error_correction</span>"
            "<br><br><span style='color:#ed125f'>To Save Settings You Have To Generate a QrCode ^^</span>";

    QMessageBox::information(this,"Help",html);
}

// Image Size : QrCode
void MainWindow::on_actionImage_Size_triggered()
{
    QDialog * d = new QDialog(this);
    QVBoxLayout * vbox = new QVBoxLayout();
    QSlider *slider = new QSlider(Qt::Horizontal);
    QLabel *label = new QLabel();
    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                        | QDialogButtonBox::Cancel);

    QObject::connect(buttonBox, &QDialogButtonBox::accepted, d, &Dialog::accept);
    QObject::connect(buttonBox,&QDialogButtonBox::rejected, d, &Dialog::reject);

    QSize mySize = this->imageSize;

    d->setWindowTitle("Image Size");
    d->resize(330,375);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(10);
    slider->setMinimum(100);
    slider->setMaximum(300);
    slider->setSingleStep(10);
    slider->setPageStep(10);
    slider->setValue(mySize.width());

    QObject::connect(slider, &QSlider::valueChanged, [&]{
        mySize.setWidth(slider->value());
        mySize.setHeight(slider->value());
        label->setFixedSize(mySize);
        label->setText(QString("%1x%2").arg(mySize.width()).arg(mySize.height()));
    });


    label->setFixedSize(mySize);
    label->setText(QString("%1x%2").arg(mySize.width()).arg(mySize.height()));
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("border:2px solid Gray;background:#eeace4");

    vbox->addWidget(label);
    vbox->addWidget(slider);
    vbox->addWidget(buttonBox);

    d->setLayout(vbox);

    int result = d->exec();
    if(result == QDialog::Accepted)
    {
        this->imageSize.setWidth(slider->value());
        this->imageSize.setHeight(slider->value());
    }
}

// Save Setting To File
void MainWindow::saveSettingToFile(const Level_QrCode &Level, const QSize &Size)
{
    /*
     * Save Format :
     * "Level*Width*Height"
     * Ex: Low*200*200
    */
    QFile file("save");
    QByteArray settings;

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        if(Level == Level_QrCode::LOW) // Error Correction QrCode: Low
            settings = QString("LOW*%1*%2").arg(Size.width()).arg(Size.height()).toLatin1();
        else if(Level == Level_QrCode::MEDIUM)
            settings = QString("MEDIUM*%1*%2").arg(Size.width()).arg(Size.height()).toLatin1();

        else if(Level == Level_QrCode::QUARTILE)
            settings = QString("QUARTILE*%1*%2").arg(Size.width()).arg(Size.height()).toLatin1();

        else if(Level == Level_QrCode::HIGH)
            settings = QString("HIGH*%1*%2").arg(Size.width()).arg(Size.height()).toLatin1();

        file.write(settings);
    }
    file.close();
}

// Get Setting From File
void MainWindow::getSettingFromFile()
{
    QFile file("save");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString line = file.readLine();
        QStringList settings = line.split("*");

        if(settings.length() != 3)// Check is correct content "3 settings"
            return;

        QString saveLevel = settings[0];
        QString saveWidth = settings[1];
        QString saveHeight = settings[2];

        if (saveLevel == "LOW")
            ui->actionLow->setChecked(true);
        else if (saveLevel == "MEDIUM")
            ui->actionMedium->setChecked(true);
        else if (saveLevel == "QUARTILE")
            ui->actionQuartile->setChecked(true);
        else if (saveLevel == "HIGH")
            ui->actionHigh->setChecked(true);
        else
            ui->actionLow->setChecked(true); // Default

        // Check Image Size is Correct
        int w = saveWidth.toInt();
        int h = saveHeight.toInt();
        if(w == h){
            if(w >=100 && w<= 300)
                this->imageSize = QSize(w,h);
        }
    }
    file.close();
}
