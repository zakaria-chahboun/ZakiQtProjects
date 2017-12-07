#include "mainwindow.h"
#include "ui_mainwindow.h"
/*~~~~~~~~~~~~~~~~~~~~~~*/
#include <zip.h>
#include <quazip.h>
#include <JlCompress.h>
/*~~~~~~~~~~~~~~~~~~~~~~*/
#include <QTime>
#include <QProcess>
#include <QFileInfo>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#define MY_TEST(msg) QMessageBox::information(this,"Test",msg)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(250,300);
}

MainWindow::~MainWindow()
{
    delete ui;
    myProcess->close();
    delete myProcess;
}

/* Choose File */
void MainWindow::on_pushButton_clicked()
{
    int i = 0;
    this->fileNames = QFileDialog::getOpenFileNames(this,"Choose File");

    ui->filesList->clear(); // clear texts :)

    QString css =
            "color: white;"
            "background-color: gray;"
            "text-decoration: none;";

    // List of All Files by Names ..
    for(const QString path : this->fileNames){
            i++;
            auto name = QFileInfo(path).fileName(); // return name of file
            auto len = this->fileNames.length(); // how many files
            auto nl = ""; // new line (if the files >= 6)
            auto tohtml = "<a href='"+path+"' style='"+css+"'>"+name+"</a>";

            if(len >= 6)
                nl = "<br>";

            ui->filesList->setText(ui->filesList->text() + tohtml +" "+ nl);
    }
}

/* Zipped! */
void MainWindow::on_pushButton_2_clicked()
{
    // Zip Name Output :)
    QString zipName = "";

    // return directory of file : at(0) or any, because all file in the same dir :)
    QString dir = QFileInfo(this->fileNames.at(0)).absoluteDir().absolutePath();

    // Default FileName & Extention :
    // if a list of files : set CurrentTime as a name ^^
    if(this->fileNames.length() > 1)
        zipName = QTime::currentTime().toString("hh-mm-ss-zz") + ".ZIP";
    // if one file : like text.txt => text.zip ^^
    else
        zipName = QFileInfo(this->fileNames.at(0)).baseName() + ".ZIP";

    // Finaly FileName as your choice :)
    QString savefile = QFileDialog::getSaveFileName(this,"Choose File",dir+"/"+zipName,"Zip Files (*.zip)");

    if(savefile.isEmpty())
        return;

    JlCompress::compressFiles(savefile,this->fileNames);
}


/*
    onMouseHover (link) : Label (fileNames)
    Display path of file in ToolTip
*/
void MainWindow::on_filesList_linkHovered(const QString &link)
{
    ui->filesList->setToolTip(link);
}

/*
    onMouseActivete (link) : Label (fileNames)
    Open Location of file/dir and select it
*/
void MainWindow::on_filesList_linkActivated(const QString &link)
{
    this->myProcess = new QProcess(this);

    QString path = QString(link).replace("/","\\");
    QString pro = "explorer.exe /select,"+path;

    myProcess->start(pro);
}
