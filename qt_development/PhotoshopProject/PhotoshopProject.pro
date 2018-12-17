TEMPLATE = app
TARGET = Photoshop Project

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    mainwindow.cpp \
    main.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h
