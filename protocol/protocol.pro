#-------------------------------------------------
#
# Project created by QtCreator 2015-08-12T14:42:10
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = protocol
TEMPLATE = lib

DEFINES += PROTOCOL_LIBRARY

SOURCES += protocol.cpp \
    ledstate.cpp

HEADERS += protocol.h\
        protocol_global.h \
    ledstate.h

CONFIG += release

CONFIG(debug, debug|release) {
    LIBS_BASE    =  debug
} else {
    LIBS_BASE    =  release
}

DESTDIR = ../$${LIBS_BASE}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
