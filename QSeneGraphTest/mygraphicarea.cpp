#include "mygraphicarea.h"

MyGraphicArea::MyGraphicArea(QWidget * parent) : QWidget(parent)
{

}


void MyGraphicArea::paintEvent(QPaintEvent *e){
    // Paiter
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Polygon
    QPolygon polygon;
    polygon << QPoint(5220,0);
    polygon << QPoint(200,0);
    polygon << QPoint(200,200);
    polygon << QPoint(0,200);

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
