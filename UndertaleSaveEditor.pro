QT	+= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET	= UndertaleSaveEditor
TEMPLATE	= app

SOURCES	+= main.cpp\
	    mainwindow.cpp

HEADERS	+= mainwindow.h

FORMS	+= mainwindow.ui

RESOURCES	+= assets.qrc

CONFIG += static

RC_ICONS = icon.ico
