#-------------------------------------------------
#
# Project created by QtCreator 2018-09-13T21:23:08
#
#-------------------------------------------------

QT       += core gui

QMAKE_LFLAGS += -static-libgcc

INCLUDEPATH += -I/usr/local/include

LIBS += -L/usr/local/lib -lopencv_imgproc -lopencv_imgcodecs -lopencv_video -lopencv_videoio -lopencv_core \
        -lopencv_highgui -lopencv_tracking

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = object-tracking
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

CONFIG += c++11

CONFIG += release
