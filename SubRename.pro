#-------------------------------------------------
#
# Project created by QtCreator 2016-12-27T21:58:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SubRename
TEMPLATE = app


SOURCES += main.cpp \
    stdafx.cpp \
    Subrename.cpp \
    impl/FinderImpl.cpp \
    impl/CopierImpl.cpp

HEADERS  += \
    stdafx.h \
    Subrename.h \
    Finder.h \
    impl/FinderImpl.h \
    Copier.h \
    Common.h \
    impl/CopierImpl.h

RESOURCES += \
    Subrename.qrc

FORMS += \
    Subrename.ui
