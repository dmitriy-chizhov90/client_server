#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T14:34:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
    clientdialog.cpp \
    manager.cpp

HEADERS  += \
    clientdialog.h \
    manager.h

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

FORMS += \
    clientdialog.ui
