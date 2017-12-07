#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// other Dialog
#include "dialog.h"

namespace Ui {
class MainWindow;
}

enum Level_QrCode{LOW,MEDIUM,QUARTILE,HIGH};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setQrCode(const QString mytext);
    void saveSettingToFile(const Level_QrCode &Level,const QSize &Size );
    void getSettingFromFile();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_actionWrite_Document_triggered();

    void on_actionScanne_Code_triggered();

    void on_actioncreator_triggered();

    void on_actionCamera_Scanne_triggered();

    void on_actionHelp_triggered();

    void on_actionImage_Size_triggered();

private:
    Ui::MainWindow *ui;
    QString fileNameJPG;
    Dialog *myDialog;
    QSize imageSize = QSize(200,200); // image size by default
    QString docTextSave;
};

#endif // MAINWINDOW_H
