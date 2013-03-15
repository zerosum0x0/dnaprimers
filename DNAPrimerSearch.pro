#-------------------------------------------------
#
# Project created by QtCreator 2013-02-28T21:50:54
#
#-------------------------------------------------

QT       += core gui

TARGET = DNAPrimerSearch
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dnasearch.cpp \
    primer.cpp \
    signalmultiplexer.cpp \
    dnadocument.cpp \
    primerprofile.cpp \
    primerfound.cpp

HEADERS  += mainwindow.h \
    dnasearch.h \
    primer.h \
    signalmultiplexer.h \
    dnadocument.h \
    primerprofile.h \
    primerfound.h

FORMS    += mainwindow.ui \
    dnadocument.ui \
    primerprofile.ui \
    primerfound.ui

RESOURCES += \
    icons.qrc
