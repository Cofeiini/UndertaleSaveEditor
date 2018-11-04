QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += network widgets

TARGET = UndertaleSaveEditor
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

win32:RC_FILE = win_ico.rc
macx:ICON = icon.icns

CONFIG += static
VERSION = 1.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

linux:QMAKE_LFLAGS += -no-pie

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    initools.cpp \
    pages.cpp \
    tools.cpp

HEADERS += \
    mainwindow.h \
    initools.h \
    pages.h \
    tools.h

RESOURCES += \
    assets.qrc
