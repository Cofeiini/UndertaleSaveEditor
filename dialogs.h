#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>

#include "mainwindow.h"
#include "tools.h"

class AboutDialog : public QDialog
{
	Q_OBJECT
public:
	AboutDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
};

class YellowNamesDialog : public QDialog
{
	Q_OBJECT
public:
	YellowNamesDialog(MainWindow *mainWindow, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
private slots:
	void checkAll();
	void uncheckAll();
private:
	CustomCheckBox *froggit;
	CustomCheckBox *whimsun;
	CustomCheckBox *moldsmal;
	CustomCheckBox *loox;
	CustomCheckBox *vegetoid;
	CustomCheckBox *migosp;
	YellowNameCheckBox *napstablook;
	CustomCheckBox *snowdrake;
	CustomCheckBox *icecap;
	CustomCheckBox *gyftrot;
	CustomCheckBox *doggo;
	CustomCheckBox *dogamyDogaressa;
	CustomCheckBox *lesserDog;
	CustomCheckBox *greaterDog;
	CustomCheckBox *aaron;
	CustomCheckBox *moldbygg;
	CustomCheckBox *woshua;
	CustomCheckBox *temmie;
	CustomCheckBox *madDummy;
	YellowNameCheckBox *shyren;
	CustomCheckBox *vulkin;
	CustomCheckBox *tsunderplane;
	CustomCheckBox *pyrope;
	CustomCheckBox *finalFroggit;
	CustomCheckBox *whimsalot;
	CustomCheckBox *astigmatism;
	CustomCheckBox *madjick;
	CustomCheckBox *knightKnight;
	CustomCheckBox *amalgamates;
};
#endif // DIALOGS_H
