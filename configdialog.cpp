#include "configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("Settings");
	setWindowIcon(QIcon(":/images/tobdog_wrench.png"));

	configTab = new QTabWidget;
	configTab->addTab(new DefaultsTab(this), "Defaults");
	configTab->addTab(new FiltersTab(this), "Filters");

	configBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(configBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(configBox, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *verticalContainer = new QVBoxLayout;
	verticalContainer->addWidget(configTab);
	verticalContainer->addWidget(configBox);
	verticalContainer->setSizeConstraint(QLayout::SetFixedSize);
	setLayout(verticalContainer);

	QObject *dTab = findChild<DefaultsTab *>("", Qt::FindChildrenRecursively);
	QObject *fTab = findChild<FiltersTab *>("", Qt::FindChildrenRecursively);

	connect(this, SIGNAL(initiator()), dTab, SLOT(initializer()));
	connect(this, SIGNAL(transmitter(QString,QVariant)), dTab, SLOT(reciever(QString,QVariant)));
	connect(this, SIGNAL(transmitter(QString,QVariant)), fTab, SLOT(reciever(QString,QVariant)));
	connect(this, SIGNAL(configTransmitter()), parent, SLOT(configReciever()));
}

void ConfigDialog::initSettings()
{
	int screen = QApplication::desktop()->screenNumber(QCursor::pos());
	int mResWidth = QApplication::desktop()->screen(screen)->width();
	int mResHeight = QApplication::desktop()->screen(screen)->height();

	QWidget *w;
	QString cName, gName;
	foreach (QWidget *var, QApplication::topLevelWidgets())
	{
		cName = var->metaObject()->className();
		if(cName == "MainWindow")
		{
			w = var;
		}
	}
	QSettings config(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationDisplayName());
	config.beginGroup("MainWindow");
	gName = config.group() + "/";
		edict[gName + "maximized"] = config.value("maximized", false);
		edict[gName + "size"] = config.value("size", QSize(w->property("minimumWidth").toInt(), w->property("minimumHeight").toInt()));
		edict[gName + "position"] = config.value("position", QPoint((mResWidth/2) - (w->property("minimumWidth").toInt()/2), (mResHeight/2) - (w->property("minimumHeight").toInt()/2)));
	config.endGroup();
	config.beginGroup("Settings");
	gName = config.group() + "/";
		edict[gName + "file"] = config.value("file", "file0");
		edict[gName + "directory"] = config.value("directory", QDir::homePath() + "/AppData/Local/UNDERTALE/");
		edict[gName + "loadfile"] = config.value("loadfile", false);
		edict[gName + "loaddir"] = config.value("loaddir", false);
		edict[gName + "confirmsave"] = config.value("confirmsave", true);
		edict[gName + "rememberlastdir"] = config.value("rememberlastdir", true);
	config.endGroup();
	config.beginGroup("Filters");
	gName = config.group() + "/";
		edict[gName + "hideboolean"] = config.value("hideboolean", false);
		edict[gName + "hidecomment"] = config.value("hidecomment", true);
		edict[gName + "hidecounter"] = config.value("hidecounter", false);
		edict[gName + "hidenumber"] = config.value("hidenumber", false);
		edict[gName + "hiderange"] = config.value("hiderange", false);
		edict[gName + "hideunused"] = config.value("hideunused", true);
	config.endGroup();
}

void ConfigDialog::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	emit initiator();
	initSettings();

	foreach(QString key, edict.keys())
	{
		transmitter(key.section("/", -1), edict.value(key));
	}
}

void ConfigDialog::boolReciever(const bool &value)
{
	QString dummy = sender()->objectName();
	foreach(QString key, edict.keys())
	{
		if(dummy == key.section("/", -1))
		{
			edict[key] = value;
		}
	}
}

void ConfigDialog::intReciever(const int &value)
{
	QString dummy = sender()->objectName();
	if(dummy == "mainw" || dummy == "mainh")
	{
		QSize mainSize = edict.value("MainWindow/size").toSize();
		if(dummy == "mainw")
		{
			mainSize.setWidth(value);
		}
		if(dummy == "mainh")
		{
			mainSize.setHeight(value);
		}
		edict["MainWindow/size"] = mainSize;
		if(!edict.value("MainWindow/maximized").toBool())
		{
			parent()->setProperty("size", mainSize);
		}
	}

	if(dummy == "mainx" || dummy == "mainy")
	{
		QPoint mainPos = edict.value("MainWindow/position").toPoint();
		if(dummy == "mainx")
		{
			mainPos.setX(value);
		}
		if(dummy == "mainy")
		{
			mainPos.setY(value);
		}
		edict["MainWindow/position"] = mainPos;
		if(!edict.value("MainWindow/maximized").toBool())
		{
			parent()->setProperty("pos", mainPos);
		}
	}
}

void ConfigDialog::stringReciever(const QString &target, const QString &value)
{
	if(target == "dir")
	{
		edict["Settings/directory"] = value;
	}
	if(target == "file")
	{
		edict["Settings/file"] = value;
	}
}

void ConfigDialog::accept()
{
	QSettings config(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationDisplayName());
	foreach(QString var, edict.keys())
	{
		config.setValue(var, edict.value(var));
	}
	emit configTransmitter();
	done(Accepted);
}

void ConfigDialog::reject()
{
	done(Rejected);
}

DefaultsTab::DefaultsTab(QWidget *parent) : QWidget(parent)
{
	QGridLayout *dialLayout = new QGridLayout;
	QGridLayout *mainLayout = new QGridLayout;

	autoDirLabel = new QLabel;
	autoFileLabel = new QLabel;
	QCheckBox *autoDir = new QCheckBox("Load Working Directory");
	QCheckBox *autoFile = new QCheckBox("Load Working File");
	QCheckBox *mainMaximized = new QCheckBox("Start Maximized");
	QCheckBox *saveNag = new QCheckBox("Confirm Overwriting");
	QCheckBox *totalRecall = new QCheckBox("Remember Last Directory");
	QDial *mainH = new QDial;
	QDial *mainW = new QDial;
	QDial *mainX = new QDial;
	QDial *mainY = new QDial;
	QLabel *mainHLabel = new QLabel;
	QLabel *mainWLabel = new QLabel;
	QLabel *mainXLabel = new QLabel;
	QLabel *mainYLabel = new QLabel;
	QPushButton *autoDirBrowse = new QPushButton("...");
	QPushButton *autoFileBrowse = new QPushButton("...");

	autoDir->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	autoDirBrowse->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	autoDirLabel->setFrameStyle(QFrame::Panel);
	autoFile->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	autoFileBrowse->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	autoFileLabel->setFrameStyle(QFrame::Panel);
	mainHLabel->setAlignment(Qt::AlignCenter);
	mainHLabel->setFrameStyle(QFrame::Panel);
	mainHLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	mainMaximized->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainWLabel->setAlignment(Qt::AlignCenter);
	mainWLabel->setFrameStyle(QFrame::Panel);
	mainWLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	mainXLabel->setAlignment(Qt::AlignCenter);
	mainXLabel->setFrameStyle(QFrame::Panel);
	mainXLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	mainYLabel->setAlignment(Qt::AlignCenter);
	mainYLabel->setFrameStyle(QFrame::Panel);
	mainYLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

	autoDir->setObjectName("loaddir");
	autoDirBrowse->setObjectName("dirbrowse");
	autoDirLabel->setObjectName("directory");
	autoFile->setObjectName("loadfile");
	autoFileBrowse->setObjectName("filebrowse");
	autoFileLabel->setObjectName("file");
	mainH->setObjectName("mainh");
	mainHLabel->setObjectName("hlabel");
	mainMaximized->setObjectName("maximized");
	mainW->setObjectName("mainw");
	mainWLabel->setObjectName("wlabel");
	mainX->setObjectName("mainx");
	mainXLabel->setObjectName("xlabel");
	mainY->setObjectName("mainy");
	mainYLabel->setObjectName("ylabel");
	saveNag->setObjectName("confirmsave");
	totalRecall->setObjectName("rememberlastdir");

	dialLayout->addWidget(mainW, 0, 0, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainWLabel, 1, 0, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainH, 0, 1, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainHLabel, 1, 1, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainX, 0, 2, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainXLabel, 1, 2, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainY, 0, 3, 1, 1, Qt::AlignJustify);
	dialLayout->addWidget(mainYLabel, 1, 3, 1, 1, Qt::AlignJustify);

	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addWidget(mainMaximized, 0, 0);
	mainLayout->addItem(dialLayout, 0, 1, 1, 4, Qt::AlignCenter);
	mainLayout->addWidget(autoFile, 1, 0);
	mainLayout->addWidget(autoFileLabel, 1, 1, 1, 4);
	mainLayout->addWidget(autoFileBrowse, 1, 5);
	mainLayout->addWidget(autoDir, 2, 0);
	mainLayout->addWidget(autoDirLabel, 2, 1, 1, 4);
	mainLayout->addWidget(autoDirBrowse, 2, 5);
	mainLayout->addWidget(saveNag, 3, 0);
	mainLayout->addWidget(totalRecall, 4, 0);
	setLayout(mainLayout);

	items.append(mainMaximized);
	items.append(mainW);
	items.append(mainWLabel);
	items.append(mainH);
	items.append(mainHLabel);
	items.append(mainX);
	items.append(mainXLabel);
	items.append(mainY);
	items.append(mainYLabel);
	items.append(autoFile);
	items.append(autoFileLabel);
	items.append(autoDir);
	items.append(autoDirLabel);
	items.append(saveNag);
	items.append(totalRecall);

	QString cName;
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(cName == "QCheckBox")
		{
			connect(var, SIGNAL(clicked(bool)), parent, SLOT(boolReciever(bool)));
		}
		if(cName == "QDial")
		{
			connect(var, SIGNAL(valueChanged(int)), parent, SLOT(intReciever(int)));
		}
	}
	connect(mainW, SIGNAL(valueChanged(int)), mainWLabel, SLOT(setNum(int)));
	connect(mainH, SIGNAL(valueChanged(int)), mainHLabel, SLOT(setNum(int)));
	connect(mainX, SIGNAL(valueChanged(int)), mainXLabel, SLOT(setNum(int)));
	connect(mainY, SIGNAL(valueChanged(int)), mainYLabel, SLOT(setNum(int)));
	connect(autoFileBrowse, SIGNAL(released()), this, SLOT(fileBrowse()));
	connect(autoDirBrowse, SIGNAL(released()), this, SLOT(fileBrowse()));
	connect(this, SIGNAL(stringTransmitter(QString, QString)), parent, SLOT(stringReciever(QString, QString)));
}

void DefaultsTab::initializer()
{
	QWidget *w;
	QString cName, oName;
	QRect desk = QApplication::desktop()->frameGeometry();

	foreach (QWidget *var, QApplication::topLevelWidgets())
	{
		cName = var->metaObject()->className();
		if(cName == "MainWindow")
		{
			w = var;
		}
	}
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		oName = var->objectName();
		if(cName == "QDial")
		{
			var->blockSignals(true);
			if(oName == "mainw")
			{
				var->setProperty("minimum", w->minimumWidth());
				var->setProperty("maximum", desk.width());
				var->setProperty("value", w->width());
			}
			if(oName == "mainh")
			{
				var->setProperty("minimum", w->minimumHeight());
				var->setProperty("maximum", desk.height());
				var->setProperty("value", w->height());
			}
			if(oName == "mainx")
			{
				var->setProperty("minimum", 0 - w->minimumWidth());
				var->setProperty("maximum", desk.x() + desk.width());
				var->setProperty("value", w->x());
			}
			if(oName == "mainy")
			{
				var->setProperty("minimum", 0 - w->minimumHeight());
				var->setProperty("maximum", desk.y() + desk.height());
				var->setProperty("value", w->y());
			}
			var->setProperty("minimumSize", QSize(75,75));
			var->setProperty("maximumSize", QSize(75,75));
			var->setProperty("notchesVisible", true);
			var->setProperty("notchTarget", 14.8);
			var->blockSignals(false);
		}
		if(cName == "QLabel")
		{
			if(oName == "wlabel")
			{
				var->setProperty("text", w->width());
			}
			if(oName == "hlabel")
			{
				var->setProperty("text", w->height());
			}
			if(oName == "xlabel")
			{
				var->setProperty("text", w->x());
			}
			if(oName == "ylabel")
			{
				var->setProperty("text", w->y());
			}
		}
	}
}

void DefaultsTab::fileBrowse()
{
	QString dummy = sender()->objectName();

	if(dummy == "filebrowse")
	{
		QString target = QFileDialog::getOpenFileName(this, "Choose File", workDir.absolutePath());
		if(target == NULL)
		{
			return;
		}
		workFile.setFileName(target.section("/", -1));
		autoFileLabel->setText(workFile.fileName());
		emit stringTransmitter("file", workFile.fileName());
	}
	else if(dummy == "dirbrowse")
	{
		QString target = QFileDialog::getExistingDirectory(this, "Choose Directory", workDir.absolutePath());
		if(target == NULL)
		{
			return;
		}
		workDir.setPath(target);
		autoDirLabel->setText(workDir.absolutePath());
		emit stringTransmitter("dir", workDir.absolutePath());
	}
}

void DefaultsTab::reciever(const QString &target, const QVariant &value)
{
	QString cName;
	if(target == "file")
	{
		workFile.setFileName(value.toString());
	}
	if(target == "directory")
	{
		workDir.setPath(value.toString());
	}
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(target == var->objectName())
		{
			if(cName == "QCheckBox")
			{
				var->setProperty("checked", value.toBool());
			}
			if(cName == "QDial")
			{
				var->setProperty("value", value.toInt());
			}
			if(cName == "QLabel")
			{
				var->setProperty("text", value.toString());
			}
		}
	}
}

FiltersTab::FiltersTab(QWidget *parent) : QWidget(parent)
{

	QVBoxLayout *mainLayout = new QVBoxLayout;

	QCheckBox *skipBool = new QCheckBox("Hide Boolean");
	skipBool->setObjectName("hideboolean");
	mainLayout->addWidget(skipBool);
	items.append(skipBool);

	QCheckBox *skipCount = new QCheckBox("Hide Counter");
	skipCount->setObjectName("hidecounter");
	mainLayout->addWidget(skipCount);
	items.append(skipCount);

	QCheckBox *skipRange = new QCheckBox("Hide Range");
	skipRange->setObjectName("hiderange");
	mainLayout->addWidget(skipRange);
	items.append(skipRange);

	QCheckBox *skipNull = new QCheckBox("Hide Unused");
	skipNull->setObjectName("hideunused");
	mainLayout->addWidget(skipNull);
	items.append(skipNull);

	QCheckBox *skipDull = new QCheckBox("Hide Comments");
	skipDull->setObjectName("hidecomment");
	mainLayout->addWidget(skipDull);
	items.append(skipDull);

	QCheckBox *skipNum = new QCheckBox("Hide ID Number");
	skipNum->setObjectName("hidenumber");
	mainLayout->addWidget(skipNum);
	items.append(skipNum);

	setLayout(mainLayout);

	QString cName;
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(cName == "QCheckBox")
		{
			connect(var, SIGNAL(clicked(bool)), parent, SLOT(boolReciever(bool)));
		}
	}
}

void FiltersTab::reciever(const QString &target, const QVariant &value)
{
	QString cName;
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(target == var->objectName())
		{
			if(cName == "QCheckBox")
			{
				var->setProperty("checked", value.toBool());
			}
		}
	}
}
