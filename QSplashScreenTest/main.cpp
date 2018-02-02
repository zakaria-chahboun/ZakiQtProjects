#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pic(":/spsc.png");
    QSplashScreen *spsc = new QSplashScreen(pic);
    spsc->show();

    MainWindow w;

    QTimer::singleShot(2500,spsc,SLOT(close()));
    QTimer::singleShot(2500,&w,SLOT(show()));

    return a.exec();
}
