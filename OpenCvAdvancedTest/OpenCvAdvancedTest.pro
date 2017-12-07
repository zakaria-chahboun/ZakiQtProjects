#-------------------------------------------------
#
# Project created by QtCreator 2017-12-03T22:59:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCvAdvancedTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    CVImageWidget/cvimagewidget.cpp

HEADERS  += mainwindow.h \
    CVImageWidget/cvimagewidget.h

FORMS    += mainwindow.ui

# OpenCV Path : My Variable
OPENCV_PATH = C:\Qt\OpenCV3.2.0vc14

INCLUDEPATH += $$OPENCV_PATH/opencv/build/include

LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_core320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_highgui320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_imgcodecs320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_imgproc320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_features2d320.dll
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_calib3d320.dll
# Fore Video Capture
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_videoio320.dll
# Fore Object (face detecting ..)
LIBS += $$OPENCV_PATH/mybuild/bin/libopencv_objdetect320.dll
