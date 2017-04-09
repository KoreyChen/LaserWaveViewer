#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T22:32:12
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaserViewer
TEMPLATE = app


SOURCES += main.cpp\
        laserviewer.cpp \
    wavepainterwidget.cpp

HEADERS  += laserviewer.h \
    wavepainterwidget.h

FORMS    += laserviewer.ui
