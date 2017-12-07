#ifndef CVIMAGEWIDGET_H
#define CVIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>
#include <opencv2/opencv.hpp>


class CVImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVImageWidget(QWidget *parent = 0);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:

public slots:
    void showImage(const cv::Mat& image);

private:
    void paintEvent(QPaintEvent* event);
    QImage qimage;
    cv::Mat tmp;
};

#endif // CVIMAGEWIDGET_H
