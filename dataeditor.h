#ifndef DATAEDITOR_H
#define DATAEDITOR_H

#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>

class InventoryEditor : public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(int value MEMBER value WRITE processIndex)

public:
	explicit InventoryEditor(QWidget *parent = 0);

private:
	int value;
	void processIndex(int index);
};

class PhoneEditor : public QComboBox
{
	Q_OBJECT
	Q_PROPERTY(int value MEMBER value WRITE processIndex)

public:
	explicit PhoneEditor(QWidget *parent = 0);

signals:
	void transmitData(int index);

public slots:
	void processIndex(int num);

private:
	int value;
};

#endif // DATAEDITOR_H
