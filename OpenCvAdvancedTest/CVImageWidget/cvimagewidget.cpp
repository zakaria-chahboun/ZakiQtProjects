#include "cvimagewidget.h"

CVImageWidget::CVImageWidget(QWidget *parent) : QWidget(parent)
{

}

QSize CVImageWidget::sizeHint() const
{
    return qimage.size();
}

QSize CVImageWidget::minimumSizeHint() const
{
    return qimage.size();
}

void CVImageWidget::showImage(const cv::Mat &image)
{
    // Convert the image to the RGB888 format
    switch (image.type()) {
    case CV_8UC1:
        cv::cvtColor(image, tmp, CV_GRAY2RGB);
        break;
    case CV_8UC3:
        cv::cvtColor(image, tmp, CV_BGR2RGB);
        break;
    }

    // QImage needs the data to be stored continuously in memory
    assert(tmp.isContinuous());
    // Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
    // (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
    // has three bytes.
    qimage = QImage(tmp.data, tmp.cols, tmp.rows, tmp.cols*3, QImage::Format_RGB888);

    this->setFixedSize(image.cols, image.rows);

    this->repaint();
}

void CVImageWidget::paintEvent(QPaintEvent *event)
{
    event->accept();
    // Display the image
    QPainter painter(this);
    painter.drawImage(QPoint(0,0), qimage);
    painter.end();
}
