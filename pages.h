#ifndef PAGES_H
#define PAGES_H

#include "mainwindow.h"

#include <QScrollArea>
#include <QWidget>

class PlayerPage : public QScrollArea
{
	Q_OBJECT
public:
	PlayerPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class BossesPage : public QScrollArea
{
	Q_OBJECT
public:
	BossesPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class MonstersPage : public QScrollArea
{
	Q_OBJECT
public:
	MonstersPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class LocationsPage : public QScrollArea
{
	Q_OBJECT
public:
	LocationsPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class DebugPage : public QScrollArea
{
	Q_OBJECT
public:
	DebugPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class DogPage : public QScrollArea
{
	Q_OBJECT
public:
	DogPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};

class INIPage : public QScrollArea
{
	Q_OBJECT
public:
	INIPage(MainWindow *mainWindow, QWidget *parent = nullptr);
};
#endif // PAGES_H
