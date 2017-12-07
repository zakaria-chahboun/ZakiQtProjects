#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Qtimer;
class QWinTaskbarButton;
class QWinTaskbarProgress;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *mytimer;

    QWinTaskbarButton *button;
    QWinTaskbarProgress *progress;
    int counter = 0;
};

#endif // MAINWINDOW_H
