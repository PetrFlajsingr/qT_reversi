#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T21:40:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = reversi
TEMPLATE = app


SOURCES +=\
        reversigui.cpp \
    aiplayer.cpp \
    gameinfo.cpp \
    savefiles.cpp \
    main.cpp

HEADERS  += reversigui.h \
    aiplayer.h \
    gameinfo.h \
    savefiles.h

FORMS    += reversigui.ui

RESOURCES += \
    reversiresource.qrc
CONFIG += c++11
