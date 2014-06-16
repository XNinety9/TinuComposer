#-------------------------------------------------
#
# Project created by QtCreator 2014-05-27T22:33:59
#
#-------------------------------------------------

QT       += core gui xml network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TinuComposer
TEMPLATE = app


SOURCES += main.cpp \
    maindialog.cpp \
    xmlparser.cpp \
    remotepixmaplabel.cpp \
    xmllistwriter.cpp

HEADERS  += \
    maindialog.h \
    xmlparser.h \
    remotepixmaplabel.h \
    xmllistwriter.h

FORMS    += \
    maindialog.ui
