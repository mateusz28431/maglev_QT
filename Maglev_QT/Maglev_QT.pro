#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T16:32:06
#
#-------------------------------------------------

QT       += core gui serialport

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Maglev_QT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialport.cpp \
    rtdacinterface.cpp \
    rtdacdialog.cpp \
    measures.cpp \
    jsonclass.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    serialport.h \
    rtdacinterface.h \
    rtdacdialog.h \
    measures.h \
    jsonclass.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    rtdacdialog.ui \
    settingsdialog.ui

unix|win32: LIBS += -L$$PWD/ -lRTDACAPI

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
