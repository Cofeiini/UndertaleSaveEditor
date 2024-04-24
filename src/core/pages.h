#ifndef PAGES_H
#define PAGES_H

#include <QScrollArea>
#include <QTabWidget>

class MainWindow;

class PlayerPage : public QTabWidget
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit PlayerPage(QWidget *parent = nullptr);
};

class BossesPage : public QTabWidget
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit BossesPage(QWidget *parent = nullptr);
};

class MonstersPage : public QTabWidget
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit MonstersPage(QWidget *parent = nullptr);
};

class LocationsPage : public QTabWidget
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit LocationsPage(QWidget *parent = nullptr);
};

class DebugPage : public QScrollArea
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit DebugPage(QWidget *parent = nullptr);
};

class ShrinePage : public QScrollArea
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit ShrinePage(QWidget *parent = nullptr);
};

class IniPage : public QScrollArea
{
	Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
	explicit IniPage(QWidget *parent = nullptr);
};

#endif // PAGES_H
