#include <QApplication>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

#include "dialogs.h"

AboutDialog::AboutDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
	setModal(true);
	setMinimumSize(QSize(300, 170));
	setWindowTitle(tr("About %1").arg(QApplication::applicationName()));

	QPushButton *closeButton = new QPushButton(tr("Close"));
	connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(closeButton);

	QLabel *aboutAppLabel = new QLabel(QString("<b>%1 %2</b>").arg(QApplication::applicationName()).arg(QApplication::applicationVersion()), this);
	aboutAppLabel->setAlignment(Qt::AlignCenter);
	QLabel *aboutProjectLabel = new QLabel("Project can be found at", this);
	QLabel *aboutLinkLabel = new QLabel("<a href=\"https://github.com/Cofeiini/UndertaleSaveEditor\">https://github.com/Cofeiini/UndertaleSaveEditor</a>", this);
	QLabel *aboutMadeByLabel = new QLabel("Made by <b>Cofeiini</b>.", this);
	QLabel *aboutThanksLabel = new QLabel("Thanks to <b>chaoskagami</b> and <b>Araraura</b>.", this);

	QVBoxLayout *aboutLayout = new QVBoxLayout(this);
	aboutLayout->addWidget(aboutAppLabel);
	aboutLayout->addWidget(aboutProjectLabel);
	aboutLayout->addWidget(aboutLinkLabel);
	aboutLayout->addStretch();
	aboutLayout->addWidget(aboutMadeByLabel);
	aboutLayout->addWidget(aboutThanksLabel);
	aboutLayout->addLayout(bottomLayout);
}

YellowNamesDialog::YellowNamesDialog(MainWindow *mainWindow, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f)
{
	setModal(true);
	setWindowTitle(tr("Tool for setting monster names yellow in credits"));
	setMinimumWidth(320);

	QPushButton *checkAllButton = new QPushButton(tr("Check All"));
	connect(checkAllButton, &QPushButton::clicked, this, &YellowNamesDialog::checkAll);
	QPushButton *uncheckAllButton = new QPushButton(tr("Uncheck All"));
	connect(uncheckAllButton, &QPushButton::clicked, this, &YellowNamesDialog::uncheckAll);

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(checkAllButton);
	topLayout->addWidget(uncheckAllButton);

	froggit = new CustomCheckBox(161, mainWindow, this);
	froggit->setText("Froggit");
	whimsun = new CustomCheckBox(162, mainWindow, this);
	whimsun->setText("Whimsun");
	moldsmal = new CustomCheckBox(163, mainWindow, this);
	moldsmal->setText("Moldsmal");
	loox = new CustomCheckBox(164, mainWindow, this);
	loox->setText("Loox");
	vegetoid = new CustomCheckBox(165, mainWindow, this);
	vegetoid->setText("Vegetoid");
	migosp = new CustomCheckBox(166, mainWindow, this);
	migosp->setText("Migosp");
	napstablook = new YellowNameCheckBox(67, mainWindow, this);
	napstablook->setText("Napstablook");
	snowdrake = new CustomCheckBox(167, mainWindow, this);
	snowdrake->setText("Snowdrake");
	icecap = new CustomCheckBox(168, mainWindow, this);
	icecap->setText("Ice Cap");
	gyftrot = new CustomCheckBox(169, mainWindow, this);
	gyftrot->setText("Gyftrot");
	doggo = new CustomCheckBox(170, mainWindow, this);
	doggo->setText("Doggo");
	dogamyDogaressa = new CustomCheckBox(171, mainWindow, this);
	dogamyDogaressa->setText("Dogamy & Dogaressa");
	lesserDog = new CustomCheckBox(172, mainWindow, this);
	lesserDog->setText("Lesser Dog");
	greaterDog = new CustomCheckBox(173, mainWindow, this);
	greaterDog->setText("Greater Dog");
	aaron = new CustomCheckBox(126, mainWindow, this);
	aaron->setText("Aaron");
	moldbygg = new CustomCheckBox(175, mainWindow, this);
	moldbygg->setText("Moldbygg");
	woshua = new CustomCheckBox(176, mainWindow, this);
	woshua->setText("Woshua");
	temmie = new CustomCheckBox(177, mainWindow, this);
	temmie->setText("Temmie");
	madDummy = new CustomCheckBox(178, mainWindow, this);
	madDummy->setText("Mad Dummy");
	shyren = new YellowNameCheckBox(112, mainWindow, this);
	shyren->setText("Shyren");
	vulkin = new CustomCheckBox(179, mainWindow, this);
	vulkin->setText("Vulkin");
	tsunderplane = new CustomCheckBox(180, mainWindow, this);
	tsunderplane->setText("Tsunderplane");
	pyrope = new CustomCheckBox(181, mainWindow, this);
	pyrope->setText("Pyrope");
	finalFroggit = new CustomCheckBox(182, mainWindow, this);
	finalFroggit->setText("Final Froggit");
	whimsalot = new CustomCheckBox(183, mainWindow, this);
	whimsalot->setText("Whimsalot");
	astigmatism = new CustomCheckBox(184, mainWindow, this);
	astigmatism->setText("Astigmatism");
	madjick = new CustomCheckBox(185, mainWindow, this);
	madjick->setText("Madjick");
	knightKnight = new CustomCheckBox(186, mainWindow, this);
	knightKnight->setText("Knight Knight");
	amalgamates = new CustomCheckBox(187, mainWindow, this);
	amalgamates->setText("Amalgamates");

	QVBoxLayout *scrollLayout = new QVBoxLayout;
	scrollLayout->addWidget(froggit);
	scrollLayout->addWidget(whimsun);
	scrollLayout->addWidget(moldsmal);
	scrollLayout->addWidget(loox);
	scrollLayout->addWidget(vegetoid);
	scrollLayout->addWidget(migosp);
	scrollLayout->addWidget(napstablook);
	scrollLayout->addWidget(snowdrake);
	scrollLayout->addWidget(icecap);
	scrollLayout->addWidget(gyftrot);
	scrollLayout->addWidget(doggo);
	scrollLayout->addWidget(dogamyDogaressa);
	scrollLayout->addWidget(lesserDog);
	scrollLayout->addWidget(greaterDog);
	scrollLayout->addWidget(aaron);
	scrollLayout->addWidget(moldbygg);
	scrollLayout->addWidget(woshua);
	scrollLayout->addWidget(temmie);
	scrollLayout->addWidget(madDummy);
	scrollLayout->addWidget(shyren);
	scrollLayout->addWidget(vulkin);
	scrollLayout->addWidget(tsunderplane);
	scrollLayout->addWidget(pyrope);
	scrollLayout->addWidget(finalFroggit);
	scrollLayout->addWidget(whimsalot);
	scrollLayout->addWidget(astigmatism);
	scrollLayout->addWidget(madjick);
	scrollLayout->addWidget(knightKnight);
	scrollLayout->addWidget(amalgamates);

	QWidget *scrollWindow = new QWidget();
	scrollWindow->setLayout(scrollLayout);

	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setWidget(scrollWindow);

	QPushButton *closeButton = new QPushButton(tr("Close"));
	connect(closeButton, &QPushButton::clicked, this, &QDialog::close);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(closeButton);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addLayout(topLayout);
	layout->addWidget(scrollArea);
	layout->addLayout(bottomLayout);
}

void YellowNamesDialog::checkAll()
{
	froggit->setChecked(true);
	whimsun->setChecked(true);
	moldsmal->setChecked(true);
	loox->setChecked(true);
	vegetoid->setChecked(true);
	migosp->setChecked(true);
	napstablook->setChecked(true);
	snowdrake->setChecked(true);
	icecap->setChecked(true);
	gyftrot->setChecked(true);
	doggo->setChecked(true);
	dogamyDogaressa->setChecked(true);
	lesserDog->setChecked(true);
	greaterDog->setChecked(true);
	aaron->setChecked(true);
	moldbygg->setChecked(true);
	woshua->setChecked(true);
	temmie->setChecked(true);
	madDummy->setChecked(true);
	shyren->setChecked(true);
	vulkin->setChecked(true);
	tsunderplane->setChecked(true);
	pyrope->setChecked(true);
	finalFroggit->setChecked(true);
	whimsalot->setChecked(true);
	astigmatism->setChecked(true);
	madjick->setChecked(true);
	knightKnight->setChecked(true);
	amalgamates->setChecked(true);
}

void YellowNamesDialog::uncheckAll()
{
	froggit->setChecked(false);
	whimsun->setChecked(false);
	moldsmal->setChecked(false);
	loox->setChecked(false);
	vegetoid->setChecked(false);
	migosp->setChecked(false);
	napstablook->setChecked(false);
	snowdrake->setChecked(false);
	icecap->setChecked(false);
	gyftrot->setChecked(false);
	doggo->setChecked(false);
	dogamyDogaressa->setChecked(false);
	lesserDog->setChecked(false);
	greaterDog->setChecked(false);
	aaron->setChecked(false);
	moldbygg->setChecked(false);
	woshua->setChecked(false);
	temmie->setChecked(false);
	madDummy->setChecked(false);
	shyren->setChecked(false);
	vulkin->setChecked(false);
	tsunderplane->setChecked(false);
	pyrope->setChecked(false);
	finalFroggit->setChecked(false);
	whimsalot->setChecked(false);
	astigmatism->setChecked(false);
	madjick->setChecked(false);
	knightKnight->setChecked(false);
	amalgamates->setChecked(false);
}
