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
    mathutil.cpp \
    audioscene.cpp \
    myitem.cpp \
    graphsceneitem.cpp

HEADERS  += mainwindow.h \
    framepainter.h \
    sound.h \
    mathutil.h \
    audioscene.h \
    myitem.h \
    graphsceneitem.h
FORMS    += mainwindow.ui
