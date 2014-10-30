#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T11:29:02
#
#-------------------------------------------------

QT       += core gui network webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = xhrtest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkaccessmanager.cpp \
    networkreply.cpp

HEADERS  += mainwindow.h \
    networkaccessmanager.h \
    networkreply.h

FORMS    += mainwindow.ui

RESOURCES +=

OTHER_FILES += \
    script.js \
    index.html
