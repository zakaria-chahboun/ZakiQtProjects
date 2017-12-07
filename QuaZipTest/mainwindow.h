#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QProcess;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_filesList_linkHovered(const QString &link);

    void on_filesList_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    QStringList fileNames;
    QProcess *myProcess;
};

#endif // MAINWINDOW_H
