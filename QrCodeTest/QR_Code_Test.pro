#-------------------------------------------------
#
# Project created by QtCreator 2017-11-21T18:32:54
# Zakaria Chahboun
#-------------------------------------------------

QT       += core gui svg multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "QrCode G-S 1.0"
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
    QrCodeGenerator/BitBuffer.cpp \
    QrCodeGenerator/QrCode.cpp \
    QrCodeGenerator/QrSegment.cpp \
    dialog.cpp


HEADERS  += mainwindow.h \
    QrCodeGenerator/BitBuffer.hpp \
    QrCodeGenerator/QrCode.hpp \
    QrCodeGenerator/QrSegment.hpp \
    dialog.h

RC_FILE = QrLogoIcon.rc

FORMS    += mainwindow.ui \
    dialog.ui

INCLUDEPATH += "$$PWD/QZXing/include"
LIBS += -L"$$PWD/QZXing/lib"
LIBS += -lQZXing2

RESOURCES += \
    images.qrc

CONFIG += qzxing_multimedia

DISTFILES +=
