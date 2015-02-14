#-------------------------------------------------
#
# Project created by QtCreator 2014-08-10T13:05:20
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += gtest-1.7.0/include/ \
    gtest-1.7.0/

SOURCES += main.cpp \
    gtest-1.7.0/src/gtest-all.cc \
    MyBusTrackerTest.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../buslib/release/ -lbuslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../buslib/debug/ -lbuslib
else:unix: LIBS += -L$$OUT_PWD/../buslib/ -lbuslib

INCLUDEPATH += $$PWD/../buslib
DEPENDPATH += $$PWD/../buslib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/release/libbuslib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/debug/libbuslib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/release/buslib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/debug/buslib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../buslib/libbuslib.a
