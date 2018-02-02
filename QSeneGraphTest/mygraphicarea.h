#ifndef MYGRAPHICAREA_H
#define MYGRAPHICAREA_H
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <QPolygon>

class MyGraphicArea : public QWidget
{

public:
    MyGraphicArea(QWidget * parent = 0);
    void paintEvent(QPaintEvent *e);
};

#endif // MYGRAPHICAREA_H
