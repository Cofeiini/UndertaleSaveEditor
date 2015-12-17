#include "configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) : QDialog(parent)
{
	setWindowTitle("Settings");

	configTab = new QTabWidget;
	configTab->addTab(new DefaultsTab(this), "Defaults");
	configTab->addTab(new FiltersTab(this), "Filters");

	configBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	connect(configBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(configBox, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *verticalContainer = new QVBoxLayout;
	verticalContainer->addWidget(configTab);
	verticalContainer->addWidget(configBox);
	setLayout(verticalContainer);

	QObject *dTab = findChild<DefaultsTab *>("", Qt::FindChildrenRecursively);
	QObject *fTab = findChild<FiltersTab *>("", Qt::FindChildrenRecursively);

	connect(this, SIGNAL(setter(QString,QVariant)), dTab, SLOT(setter(QString,QVariant)));
	connect(this, SIGNAL(setter(QString,QVariant)), fTab, SLOT(setter(QString,QVariant)));
}

void ConfigDialog::showEvent(QShowEvent *event)
{
	QDialog::showEvent(event);

	QSettings config(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationDisplayName());
	foreach(QString var, config.allKeys())
	{
		edict.insert(var, config.value(var));
		setter(var.section("/", -1), config.value(var));
	}
}

void ConfigDialog::boolSetter(bool value)
{
	QString dummy = sender()->objectName();
	foreach(QString var, edict.keys())
	{
		if(dummy == var.section("/", -1))
		{
			edict[var] = value;
		}
	}
}

void ConfigDialog::stringSetter(QString target, QString value)
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
	done(Accepted);
}

void ConfigDialog::reject()
{
	done(Rejected);
}

DefaultsTab::DefaultsTab(QWidget *parent) : QWidget(parent)
{
	QGridLayout *mainLayout = new QGridLayout;

	QCheckBox *autoFile = new QCheckBox("Load Working File");
	autoFile->setObjectName("loadfile");
	autoFile->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(autoFile, 0, 0);
	items.append(autoFile);

	autoFileLabel = new QLabel();
	autoFileLabel->setText(workFile.fileName());
	autoFileLabel->setObjectName("file");
	autoFileLabel->setFrameStyle(QFrame::Panel);
	mainLayout->addWidget(autoFileLabel, 0, 1);
	items.append(autoFileLabel);

	QPushButton *autoFileBrowse = new QPushButton("...");
	autoFileBrowse->setObjectName("filebrowse");
	autoFileBrowse->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(autoFileBrowse, 0, 2);

	QCheckBox *autoDir = new QCheckBox("Load Working Directory");
	autoDir->setObjectName("loaddir");
	autoDir->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(autoDir, 1, 0);
	items.append(autoDir);

	autoDirLabel = new QLabel(workDir.absolutePath());
	autoDirLabel->setObjectName("directory");
	autoDirLabel->setFrameStyle(QFrame::Panel);
	mainLayout->addWidget(autoDirLabel, 1, 1);
	items.append(autoDirLabel);

	QPushButton *autoDirBrowse = new QPushButton("...");
	autoDirBrowse->setObjectName("dirbrowse");
	autoDirBrowse->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	mainLayout->addWidget(autoDirBrowse, 1, 2);

	QCheckBox *saveNag = new QCheckBox("Confirm Overwriting");
	saveNag->setObjectName("confirmsave");
	mainLayout->addWidget(saveNag, 2, 0);
	items.append(saveNag);

	QCheckBox *totalRecall = new QCheckBox("Remember Last Directory");
	totalRecall->setObjectName("rememberlastdir");
	mainLayout->addWidget(totalRecall, 3, 0);
	items.append(totalRecall);

	setLayout(mainLayout);

	QString cName;
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(cName == "QCheckBox")
		{
			connect(var, SIGNAL(clicked(bool)), parent, SLOT(boolSetter(bool)));
		}
	}
	connect(autoFileBrowse, SIGNAL(released()), this, SLOT(fileBrowse()));
	connect(autoDirBrowse, SIGNAL(released()), this, SLOT(fileBrowse()));
	connect(this, SIGNAL(stringSender(QString, QString)), parent, SLOT(stringSetter(QString, QString)));
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
		emit stringSender("file", workFile.fileName());
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
		emit stringSender("dir", workDir.absolutePath());
	}
}

void DefaultsTab::setter(const QString &target, const QVariant &value)
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

	QCheckBox *skipCount = new QCheckBox("Hide Counter");
	skipCount->setObjectName("hidecounter");
	mainLayout->addWidget(skipCount);

	QCheckBox *skipRange = new QCheckBox("Hide Range");
	skipRange->setObjectName("hiderange");
	mainLayout->addWidget(skipRange);

	QCheckBox *skipNull = new QCheckBox("Hide Unused");
	skipNull->setObjectName("hideunused");
	mainLayout->addWidget(skipNull);

	QCheckBox *skipDull = new QCheckBox("Hide Comments");
	skipDull->setObjectName("hidecomment");
	mainLayout->addWidget(skipDull);

	QCheckBox *skipNum = new QCheckBox("Hide ID Number");
	skipNum->setObjectName("hidenumber");
	mainLayout->addWidget(skipNum);

	setLayout(mainLayout);

	items.append(skipBool);
	items.append(skipCount);
	items.append(skipRange);
	items.append(skipNull);
	items.append(skipDull);
	items.append(skipNum);

	QString cName;
	foreach (QWidget *var, items)
	{
		cName = var->metaObject()->className();
		if(cName == "QCheckBox")
		{
			connect(var, SIGNAL(clicked(bool)), parent, SLOT(boolSetter(bool)));
		}
	}
}

void FiltersTab::setter(const QString &target, const QVariant &value)
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
