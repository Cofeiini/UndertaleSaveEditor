QT	+= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET	= UndertaleSaveEditor
TEMPLATE	= app

SOURCES	+= main.cpp\
	    mainwindow.cpp \
    configdialog.cpp

HEADERS	+= mainwindow.h \
    configdialog.h

FORMS	+= mainwindow.ui

RESOURCES	+= assets.qrc

CONFIG += static

RC_ICONS = icon.ico
