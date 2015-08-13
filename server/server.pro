#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T10:14:37
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app

SOURCES += main.cpp\
        server.cpp \
    manager.cpp \
    deviceemulator.cpp

HEADERS  += server.h \
    manager.h \
    deviceemulator.h

INCLUDEPATH += ../protocol

CONFIG += release

CONFIG(debug, debug|release) {
    LIBS_BASE    =  debug
} else {
    LIBS_BASE    =  release
}

DESTDIR = ../$${LIBS_BASE}

LIBS += -L../$${LIBS_BASE} \
        -lprotocol

