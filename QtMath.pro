#-------------------------------------------------
#
# Project created by QtCreator 2014-07-14T21:07:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMath
TEMPLATE = app

LIBS += -lasound

SOURCES += main.cpp\
        mainwindow.cpp \
    framepainter.cpp \
    sound.cpp \
    mathutil.cpp

HEADERS  += mainwindow.h \
    framepainter.h \
    sound.h \
    mathutil.h

FORMS    += mainwindow.ui
