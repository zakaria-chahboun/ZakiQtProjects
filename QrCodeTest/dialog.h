#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QTemporaryFile>
namespace Ui {
class Dialog;
}

class QImage;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    void closeEvent(QCloseEvent *e);
    void decodeQrCode();
    void listOfAvailableCameras();
    ~Dialog();

private slots:
    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnScanne_clicked();

    void on_toolButton_clicked();

    void on_listCameras_activated(const QString &arg1);

private:
    Ui::Dialog *ui;

    QCamera *myCamera;
    QCameraViewfinder *myCameraViewFinder;
    QCameraImageCapture *myCameraCapture;

    QImage myTmpImage;
    QTemporaryFile MyTempFile;
};

#endif // DIALOG_H
