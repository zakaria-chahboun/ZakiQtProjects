#include "mainwindow.h"
#include "ui_mainwindow.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>
//~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <QIcon>
#include <QTimer>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->counter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete button;
    delete mytimer;
    delete progress;
}

/* onClick Button */
/* Show Progress in TaskBar with icon in Windows >= 7 */
void MainWindow::on_pushButton_clicked()
{
    /*
     * Note: QWidget::windowHandle() returns a valid instance of a QWindow
       only after the widget has been shown
    */

    /* Simple Code ^^ */
    this->button = new QWinTaskbarButton(this);
        button->setWindow(this->windowHandle());
        button->setOverlayIcon(QIcon(":/loading clock.png"));

    this->progress = this->button->progress();
    this->progress->setVisible(true);


    /* just for play :p */
    this->mytimer = new QTimer(this);

    connect(this->mytimer, &QTimer::timeout, [&](){
        this->progress->setValue(this->counter);
        this->counter += 5;

        if(this->counter > 100)
            this->mytimer->stop();
    });
    this->mytimer->start(100);
}

/* Close Event ^^ */
void MainWindow::closeEvent(QCloseEvent *event){
    this->mytimer->stop();
    event->accept();
}
