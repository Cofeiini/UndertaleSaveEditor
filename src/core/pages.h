#ifndef PAGES_H
#define PAGES_H

#include <QScrollArea>
#include <QTabWidget>

class MainWindow;

class PlayerPage : public QTabWidget
{
	Q_OBJECT // NOLINT

public:
	PlayerPage(QWidget *parent = nullptr);
};

class BossesPage : public QTabWidget
{
	Q_OBJECT // NOLINT

public:
	BossesPage(QWidget *parent = nullptr);
};

class MonstersPage : public QTabWidget
{
	Q_OBJECT // NOLINT

public:
	MonstersPage(QWidget *parent = nullptr);
};

class LocationsPage : public QTabWidget
{
	Q_OBJECT // NOLINT

public:
	LocationsPage(QWidget *parent = nullptr);
};

class DebugPage : public QScrollArea
{
	Q_OBJECT // NOLINT

public:
	DebugPage(QWidget *parent = nullptr);
};

class ShrinePage : public QScrollArea
{
	Q_OBJECT // NOLINT

public:
	ShrinePage(QWidget *parent = nullptr);
};

class IniPage : public QScrollArea
{
	Q_OBJECT // NOLINT

public:
	IniPage(QWidget *parent = nullptr);
};

#endif // PAGES_H
