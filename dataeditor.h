#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include <QWidget>
#include <QComboBox>
#include <QDebug>
#include <QFile>
#include <QStandardItemModel>
#include <QTextStream>

class DataEditor : public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(int value MEMBER value WRITE recieveValue)

public:
	DataEditor(QWidget *parent = 0, int index = 0);
	void InventoryEditor();
	void StatusEditor(int index = 0);

signals:
	void transmitData(int num);

public slots:
	void trueIndexValue(int num);

private:
	int value;
	int id;
	QStringList rooms;
	void recieveValue(int num);
};

class PhoneEditor : public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(int value MEMBER value WRITE recieveValue)

public:
	PhoneEditor(QWidget *parent = 0);

signals:
	void transmitData(int index);

public slots:
	void recieveValue(int num);

private:
	int value;
};

#endif // DATAEDITOR_H
