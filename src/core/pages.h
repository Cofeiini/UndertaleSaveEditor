#ifndef PAGES_H
#define PAGES_H

#include <QScrollArea>
#include <QTabWidget>

class MainWindow;

class PlayerPage : public QTabWidget
{
	Q_OBJECT

public:
	PlayerPage(QWidget *parent = nullptr);
};

class BossesPage : public QTabWidget
{
	Q_OBJECT

public:
	BossesPage(QWidget *parent = nullptr);
};

class MonstersPage : public QTabWidget
{
	Q_OBJECT

public:
	MonstersPage(QWidget *parent = nullptr);
};

class LocationsPage : public QTabWidget
{
	Q_OBJECT

public:
	LocationsPage(QWidget *parent = nullptr);
};

class DebugPage : public QScrollArea
{
	Q_OBJECT

public:
	DebugPage(QWidget *parent = nullptr);
};

class ShrinePage : public QScrollArea
{
	Q_OBJECT

public:
	ShrinePage(QWidget *parent = nullptr);
};

class IniPage : public QScrollArea
{
	Q_OBJECT

public:
	IniPage(QWidget *parent = nullptr);
};

#endif // PAGES_H
