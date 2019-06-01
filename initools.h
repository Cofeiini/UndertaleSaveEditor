#ifndef INITOOLS_H
#define INITOOLS_H

#include "mainwindow.h"

#include <QCheckBox>
#include <QLineEdit>
#include <QSpinBox>

class IniCheckBox : public QCheckBox
{
	Q_OBJECT
public:
	IniCheckBox(QString id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(int i);
	void updateData();
private:
	QString id;
	int values[3] = {0, 1, 1};
	QMap<int, Qt::CheckState> states = { {0, Qt::Unchecked}, {1, Qt::Checked} };
	MainWindow *mw;
};

class IniLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	IniLineEdit(QString id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateSave(QString text);
	void updateData();
private:
	QString id;
	MainWindow *mw;
};

class IniSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	IniSpinBox(QString id, MainWindow *mainWindow, QWidget *parent = nullptr);
signals:
	void dataChanged(bool value);
public slots:
	void updateIni(int i);
	void updateData();
private:
	QString id;
	MainWindow *mw;
};

class HorizontalLine : public QFrame
{
	Q_OBJECT
public:
	HorizontalLine(QWidget *parent = nullptr);
};

class VerticalLine : public QFrame
{
	Q_OBJECT
public:
	VerticalLine(QWidget *parent = nullptr);
};

#endif // INITOOLS_H
