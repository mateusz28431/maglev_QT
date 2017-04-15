#-------------------------------------------------
#
# Project created by QtCreator 2017-03-02T16:32:06
#
#-------------------------------------------------

QT       += core gui serialport printsupport

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
    settingsdialog.cpp \
    terminaldialog.cpp \
    plotsdialog.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    serialport.h \
    rtdacinterface.h \
    rtdacdialog.h \
    measures.h \
    jsonclass.h \
    settingsdialog.h \
    terminaldialog.h \
    plotsdialog.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    rtdacdialog.ui \
    settingsdialog.ui \
    terminaldialog.ui \
    plotsdialog.ui

unix|win32: LIBS += -L$$PWD/ -lRTDACAPI

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
