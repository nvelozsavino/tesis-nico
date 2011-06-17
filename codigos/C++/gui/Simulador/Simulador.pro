#-------------------------------------------------
#
# Project created by QtCreator 2011-06-16T15:45:51
#
#-------------------------------------------------

QT       += core gui

TARGET = Simulador
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:/dev/OpenCV-2.2.0/include/opencv \
C:/dev/OpenCV-2.2.0/include/opencv2
LIBS+= C:/dev/OpenCV-2.2.0/MinGW/lib/*.a

