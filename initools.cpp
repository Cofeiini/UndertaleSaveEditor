#include "initools.h"

IniCheckBox::IniCheckBox(QString id, MainWindow *mainWindow, QWidget *parent) : QCheckBox(parent), id(id), mw(mainWindow)
{
	connect(this, SIGNAL(stateChanged(int)), this, SLOT(updateSave(int)));
	connect(mw, SIGNAL(updateIniWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(iniModified(bool)));
}
void IniCheckBox::updateSave(int i)
{
	mw->iniData.insert(id, values[i]);
	emit dataChanged(true);
}
void IniCheckBox::updateData()
{
	setCheckState(states.value(static_cast<int>(mw->iniData.value(id).toDouble())));
}

IniLineEdit::IniLineEdit(QString id, MainWindow *mainWindow, QWidget *parent) : QLineEdit(parent), id(id), mw(mainWindow)
{
	connect(this, SIGNAL(textEdited(QString)), this, SLOT(updateSave(QString)));
	connect(mw, SIGNAL(updateIniWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(iniModified(bool)));
}
void IniLineEdit::updateSave(QString text)
{
	mw->iniData.insert(id, text);
	emit dataChanged(true);
}
void IniLineEdit::updateData()
{
	setText(mw->iniData.value(id).toString());
}

IniSpinBox::IniSpinBox(QString id, MainWindow *mainWindow, QWidget *parent) : QSpinBox(parent), id(id), mw(mainWindow)
{
	setRange(INT_MIN, INT_MAX);

	connect(this, SIGNAL(valueChanged(int)), this, SLOT(updateIni(int)));
	connect(mw, SIGNAL(updateIniWidgets()), this, SLOT(updateData()));
	connect(this, SIGNAL(dataChanged(bool)), mw, SLOT(iniModified(bool)));
}
void IniSpinBox::updateIni(int i)
{
	mw->iniData.insert(id, i);
	emit dataChanged(true);
}
void IniSpinBox::updateData()
{
	setValue(static_cast<int>(mw->iniData.value(id).toDouble()));
}

HorizontalLine::HorizontalLine(QWidget *parent) : QFrame(parent)
{
	setFixedHeight(3);
	setLineWidth(1);
	setFrameShadow(QFrame::Sunken);
	setFrameShape(QFrame::HLine);
}

VerticalLine::VerticalLine(QWidget *parent) : QFrame(parent)
{
	setFixedWidth(3);
	setLineWidth(1);
	setFrameShadow(QFrame::Sunken);
	setFrameShape(QFrame::VLine);
}
