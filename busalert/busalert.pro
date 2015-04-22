#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T23:11:02
#
#-------------------------------------------------

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = busalert
TEMPLATE = app

CONFIG += c++11

SOURCES += busalert/main.cpp\
        busalert/MainWindow.cpp \
    busalert/EditStopDialog.cpp \
    busalert/StopArrivalsWindow.cpp \
    busalert/AvailableStopsDialog.cpp \
    busalert/StopCodeValidator.cpp \
    busalert/Application.cpp \
    busalert/SavedStopsModel.cpp \
    busalert/NoStopSelectedWidget.cpp \
    busalert/AboutBox.cpp \
    busalert/ArrivalsModel.cpp

HEADERS  += busalert/MainWindow.h \
    busalert/EditStopDialog.h \
    busalert/ApiKey.h \
    busalert/StopArrivalsWindow.h \
    busalert/AvailableStopsDialog.h \
    busalert/StopCodeValidator.h \
    busalert/Application.h \
    busalert/SavedStopsModel.h \
    busalert/NoStopSelectedWidget.h \
    busalert/AboutBox.h \
    busalert/ArrivalsModel.h

FORMS    += busalert/MainWindow.ui \
    busalert/EditStopDialog.ui \
    busalert/StopArrivalsWindow.ui \
    busalert/AvailableStopsDialog.ui \
    busalert/NoStopSelectedWidget.ui \
    busalert/AboutBox.ui

RESOURCES += \
    busalert.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../buslib/release/ -lbuslib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../buslib/debug/ -lbuslib
else:unix: LIBS += -L$$OUT_PWD/../buslib/ -lbuslib

INCLUDEPATH += $$PWD/../buslib \
    $$PWD

DEPENDPATH += $$PWD/../buslib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/release/libbuslib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/debug/libbuslib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/release/buslib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../buslib/debug/buslib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../buslib/libbuslib.a
