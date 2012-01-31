#-------------------------------------------------
#
# Project created by QtCreator 2011-12-21T10:56:13
#
#-------------------------------------------------

QT       += core gui

TARGET = analizador
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linefinder.cpp \
    controller.cpp

HEADERS  += mainwindow.h \
    linefinder.h \
    controller.h

FORMS    += mainwindow.ui

PKGCONFIG += opencv


INCLUDEPATH += `pkg-config opencv --cflags`
LIBS += `pkg-config opencv --libs`


