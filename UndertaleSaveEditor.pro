CONFIG += static
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui
RC_ICONS = icon.ico
TARGET = UndertaleSaveEditor
TEMPLATE = app
VERSION = 0.1

FORMS += mainwindow.ui

HEADERS += mainwindow.h\
        configdialog.h

RESOURCES += assets.qrc

SOURCES += main.cpp\
        mainwindow.cpp\
        configdialog.cpp
