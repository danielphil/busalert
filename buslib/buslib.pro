#-------------------------------------------------
#
# Project created by QtCreator 2014-08-10T13:14:46
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = buslib
TEMPLATE = lib

CONFIG += staticlib
CONFIG += c++11

SOURCES += buslib/MyBusTracker.cpp \
    buslib/Error.cpp \
    buslib/DataDownloader.cpp \
    buslib/TopologyId.cpp \
    buslib/BusStops.cpp \
    buslib/BusStop.cpp \
    buslib/StopTimes.cpp \
    buslib/Arrival.cpp

HEADERS += buslib/MyBusTracker.h \
    buslib/Error.h \
    Maybe.h \
    buslib/DataDownloader.h \
    buslib/TopologyId.h \
    buslib/BusStops.h \
    buslib/BusStop.h \
    buslib/StopTimes.h \
    buslib/Arrival.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD
