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
    sound.cpp \
    mathutil.cpp \
    audioscene.cpp \
    ball.cpp \
    rawinfodialog.cpp \
    dialogmakegraph.cpp

HEADERS  += mainwindow.h \
    sound.h \
    mathutil.h \
    audioscene.h \
    ball.h \
    rawinfodialog.h \
    dialogmakegraph.h
FORMS    += mainwindow.ui \
    rawinfodialog.ui \
    dialogmakegraph.ui
