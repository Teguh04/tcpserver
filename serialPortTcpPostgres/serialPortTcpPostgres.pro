#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T14:30:09
#
#-------------------------------------------------

QT       += core gui serialport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serialPortTcpPostgres
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connection.cpp

HEADERS  += mainwindow.h \
    connection.h

FORMS    += mainwindow.ui
