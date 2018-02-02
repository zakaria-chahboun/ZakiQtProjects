#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPen>
#include <QFile>
#include <QBrush>
#include <QPoint>
#include <QRegExp>
#include <QPolygon>
#include <QPainter>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainterPath>
#include <QDoubleValidator>
#include <QItemSelectionModel>
#include <QKeySequence>
#include <QPolygonF>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init GraphicsView
    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(this->scene);

    // init TableView
    QStringList lablesList;
    lablesList << "X" << "Y";
    ui->tableWidget->setHorizontalHeaderLabels(lablesList);

    // add default X,Y coordinates point
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::number(0)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString::number(0)));

    // set Validator
    QDoubleValidator *doubleOnly = new QDoubleValidator(this);
    ui->X->setValidator(doubleOnly);
    ui->Y->setValidator(doubleOnly);
    ui->H->setValidator(doubleOnly);
    ui->W->setValidator(doubleOnly);

    // Remove btn (Shorcut)
    ui->pushButton_4->setShortcut(QKeySequence::Delete);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

void MainWindow::paintEvent(QPaintEvent *e){
    // Paiter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Polygon
    QPolygon polygon;
    polygon << QPoint(10,10);
    polygon << QPoint(210,10);
    polygon << QPoint(210,210);
    polygon << QPoint(10,210);

    // Pen
    QPen linepen;
    linepen.setWidth(5);
    linepen.setColor(Qt::red);

    // Brush
    QBrush fill;
    fill.setColor(Qt::yellow);
    fill.setStyle(Qt::SolidPattern);

    // fill
    QPainterPath path;
    path.addPolygon(polygon);

    // set Pen to Painter
    painter.setPen(linepen);
    // draw Polygon on Painter
    painter.drawPolygon(polygon);
    // fill on painter
    painter.fillPath(path,fill);
}

// on : click : Draw Rectangle : Add btn
void MainWindow::on_btnAdd_clicked()
{
    qreal x = ui->X->text().toDouble();
    qreal y = ui->Y->text().toDouble();
    qreal h = ui->H->text().toDouble();
    qreal w = ui->W->text().toDouble();


    // pen
    QPen pen;
    pen.setWidth(6);
    pen.setColor(QColor("#aa00aa"));

    // brush
    QBrush brush;
    brush.setColor(Qt::white);

    this->scene->clear();
    this->rect = this->scene->addRect(x,y,w,h,pen,brush);
}

// on : click : New Point btn (Table)
void MainWindow::on_pushButton_3_clicked()
{
    auto rowCount = ui->tableWidget->rowCount();
    // clear selections :)
    ui->tableWidget->clearSelection();

    // add new row
    ui->tableWidget->insertRow(rowCount);

    // add X,Y coordinates point : by default = 0
    ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(QString::number(0)));
    ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(QString::number(0)));
}

// on click : Draw Graph btn (Drawing Area)
void MainWindow::on_pushButton_clicked()
{
    int row = 0;
    int col1 = 0; // first
    int col2 = 1; // second
    int rowCount = ui->tableWidget->rowCount();

    // pen
    QPen pen;
    pen.setWidth(6);
    pen.setColor(QColor("#aa00aa"));

    // Clear Scene (Area) :)
    this->scene->clear();

    // polygon :)
    //QPolygonF pol;

    // Line :)
    QLineF li;

    QList<QPointF> tmpList;


    // get Infos (from rows cols)
    for(row; row<rowCount; row++){
        QTableWidgetItem *currItem1 = ui->tableWidget->item(row,col1);
        QTableWidgetItem *currItem2 = ui->tableWidget->item(row,col2);

        QPointF p;
        p.setX(currItem1->data(0).toDouble());
        p.setY(currItem2->data(0).toDouble());

        tmpList << p;

        //pol << p;
    }

    // Draw Line
    for(int i=0; i<rowCount; i++){
        if(i == rowCount-1)
            break;

        li.setP1(tmpList[i]);
        li.setP2(tmpList[i+1]);

        this->scene->addLine(li,pen);
    }

    //this->poItem = this->scene->addPolygon(pol,pen);
}

// on click : Remove Row(s)
void MainWindow::on_pushButton_4_clicked()
{
    QItemSelectionModel *select = ui->tableWidget->selectionModel();

    if(!select->hasSelection())
        return;

    QModelIndexList selectedrows = select->selectedRows();
    int firstIndex = selectedrows.first().row();
    int rowCount = selectedrows.count();

    for(int i = 0; i < rowCount; i++){
        ui->tableWidget->removeRow(firstIndex);
    }
}

// on click : Reset Row(s)
void MainWindow::on_pushButton_2_clicked()
{
    auto rc = ui->tableWidget->rowCount();
    auto i = 0;

    while (i < rc) {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(0)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(0)));
        i++;
    }
}

// read file : btn
void MainWindow::on_pushButton_5_clicked()
{
    auto filename = QFileDialog::getOpenFileName(this,
          tr("Open Points File"), "", tr("Simple File (*.txt)"));
    if(filename.isEmpty())
        return;

    auto rowCount = ui->tableWidget->rowCount();
    auto i = 0;
    auto newConter = 0;
    QStringList list;
    QFile file(filename);

    /* check file */
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Cannot Open File!","The file cannot opened!"
                                "\nmaybe there are some problems with the contents!");
        return;
    }

    /* clean table :) */
    while(i < rowCount){
        ui->tableWidget->removeRow(0);
        i++;
    }

    /* read file content */
    while (!file.atEnd()) {
        auto line = QString(file.readLine());
        line.remove("\n");
        list = line.split(","); // format is : x,y
        qDebug() << line;
        qDebug() << list;

        // check if correct format
        QRegExp re("[-+]?[0-9]+\\.?[0-9]*");
        if(list.length() != 2 || !re.exactMatch(list.first()) || !re.exactMatch(list.last())){
            QMessageBox::warning(this,"Error!","The file Contain a non numeric content!<br>"
                                 "<b>at line : " + QString::number(newConter+1)+"</b>");
            break;
        }

        // add new x,y infos :)
        ui->tableWidget->insertRow(newConter);
        ui->tableWidget->setItem(newConter,0,new QTableWidgetItem(list.first()));
        ui->tableWidget->setItem(newConter,1,new QTableWidgetItem(list.last()));

        newConter ++;
    }

    file.close(); // Good Programmer :)
}

// save infos to file : btn
void MainWindow::on_pushButton_6_clicked()
{
    auto filename = QFileDialog::getSaveFileName(this,
          tr("Save Points File"), "", tr("Simple File (*.txt)"));

    if(filename.isEmpty())
        return;

    // Create Saved File
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,"Cannot Save File!","The file cannot writed!");
        return;
    }

    auto rowCount = ui->tableWidget->rowCount();
    auto i = 0;
    QTextStream out(&file);

    while (i < rowCount) {
        auto firstCol = ui->tableWidget->item(i,0)->text();
        auto secondCol = ui->tableWidget->item(i,1)->text();

        out << firstCol + "," + secondCol + "\n";
        i++;
    }

    file.close();
    // http://www.walletfox.com/course/qtableviewcopypaste.php
}
