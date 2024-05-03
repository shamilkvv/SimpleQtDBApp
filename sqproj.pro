TEMPLATE = app
CONFIG += console c++20
CONFIG -= app_bundle

SOURCES += \
        dbmanager.cpp \
        gui.cpp \
        main.cpp

HEADERS += \
    dbmanager.h \
    gui.h

QT += widgets
QT += core gui
QT += sql

QT += qml
