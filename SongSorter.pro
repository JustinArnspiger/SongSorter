#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T23:25:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
CONFIG += c++14

TARGET = SongSorter
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    songHandling/song.cpp \
    UI/startupwindow.cpp \
    UI/comparisonwindow.cpp \
    UI/songlistviewerwindow.cpp

HEADERS += \
    songHandling/song.h \
    UI/startupwindow.h \
    UI/comparisonwindow.h \
    UI/songlistviewerwindow.h


FORMS += \
    UI/comparisonwindow.ui \
    UI/startupwindow.ui \
    UI/songlistviewerwindow.ui

win32: LIBS += -L$$PWD/taglib/lib/ -llibtag.dll

INCLUDEPATH += $$PWD/taglib/include
DEPENDPATH += $$PWD/taglib/include

DISTFILES += \
    doc/documentation.dox
