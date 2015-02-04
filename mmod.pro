#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T17:34:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

TARGET = mmod
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    viewport.cpp

HEADERS  += mainwindow.h \
    viewport.h
