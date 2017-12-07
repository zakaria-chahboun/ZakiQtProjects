#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class MainWindow;
}

class CVImageWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void timerEvent(QTimerEvent *event);
    void myfaceDetect(bool run = true);
    ~MainWindow();

private slots:
    void on_btnStartCamera_clicked();
    void on_checkBoxFaceDetect_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    CVImageWidget* imageWidget;
    cv::VideoCapture mycap;
    cv::Mat myImgFrame;
    int MyTimerID;
    bool runDetectFace;
};

#endif // MAINWINDOW_H
