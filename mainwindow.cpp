/*
			  hsssssN       msssssd               	Howdy!
		 ms--hyhy---/++o  o+/----yds--hN          	This is the SOURCE CODE for Undertale Save Editor by Cofeiini.
		s-  ``om   NNNNNNNNNN     s``  :h
		 h+o   dsss          .sssm  N++m          	hmm...
  mo....om   d:`    -:.   -:.    `+d   d+....sm   	You're new here, aren'tcha?
N+.``````o N:       dMy   dMs      `/  /````` -sN
   -oooom  N        dMy   dMs       `   hoooo.  - 	Golly, you must be so confused.
::.     `o N    `:  oh+   sh/  :`   `  /`     -:+ 	Someone ought to teach you how things work around here.
  mo`    +N h`  `:shysssssssyhs:`  -d m-    .sm   	I guess little old me will have to do.
	Nsssssy  s.    +ossssssso/    :y  ssssss
		dyo.   y-    ```````    :d  N`sym
	  d:` `-ddN Ndd----------/dd  Ndd-  .+m
	 N   :s/  :++o             +++- `+s.  .
	 N   :+         :++o +++-         o.  .
	  dd+------sddddN       Ndddd+------sdm
					 y/oN
					-
				   .  `/m
				   .  /N
					-  `o
					Ns-  `m
					  Ns  -h
					  d/   :h
				h-  h:      + N`m
				Nh+dd+-----sdh+d
				   y++++++++oh

But seriously...
My work probably breaks every programming standards and every possible from of "best practices".
I'll improve this code as I learn more about Qt... I promise.

For now, I had no need for commenting. Instead I used debug output.
To me those debug lines are as good as comments, but to an "outsider" this might seem like a huge mess. Which it totally is.
Since I'm the only programmer in this project, I won't be adding comments any time soon.

Feel free to correct me on practically anything.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mResWidth = QApplication::desktop()->screen(-1)->width();
	mResHeight = QApplication::desktop()->screen(-1)->height();
	unitReady = false;
	stats.fill(0,4);
	fileWasModified(0);
	setWindowFilePath(NULL);
	readSettings();
	setupMenuBar();

	setupEntries();

	// After loading defaults from settings, we need to update the "StatusTips" of these entries in the options.
	ui->actionConfigUseEdictDir->setStatusTip(QString("Appointed directory: %1").arg(edictDir.path()));
	ui->actionConfigUseEdictFile->setStatusTip(QString("Appointed file: %1").arg(edictFile));
	ui->actionConfigSetEdictDir->setStatusTip(QString("Current Working directory: %1").arg(edictDir.path()));
	ui->actionConfigSetEdictFile->setStatusTip(QString("Current Working file: %1").arg(edictFile));

	qDebug() << "FINAL workDir: " << workDir.path();
	qDebug() << "FINAL workFile: " << workFile;
	setWindowTitle(TITLELABEL);
}

void MainWindow::showEvent(QShowEvent *event)
{
	// Due to spacers in the ui, interface elements will overlap each other after the ui is displayed. The "update()" at the end remedies this problem.
	QMainWindow::showEvent(event);
	unitReady = true;
	if(MainWindow::width() < MainWindow::minimumWidth() || MainWindow::height() < MainWindow::minimumHeight())
	{
		resize(MainWindow::minimumWidth(), MainWindow::minimumHeight());
	}

	if(MainWindow::x() > QApplication::desktop()->width() || MainWindow::y() > QApplication::desktop()->height())
	{
		move((mResWidth/2) - (MainWindow::minimumWidth()/2), (mResHeight/2) - (MainWindow::minimumHeight()/2));
	}
	displayInfo();
	ui->contentLayout->update();
}

void MainWindow::setupEntries()
{

	// Using OverrideCursor because this phase takes forever. User input during this phase leads to bad times
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	if(mem0.size() < 549)
	{
		qDebug() << "filling empty mem0";
		for(int i = 1; i < 550; i++)
		{
			mem0[i] = "";
		}
	}

	int size = mem0.size();
	for(int i = 0; i < size; i++)
	{
		QString curType = mem2.value(i+1);
		QString val = mem0.value(i+1);
		if(curType == "bool")
		{
			// CheckBox, strangely, can be in three states. This fact of course needlessly complicates things.
			QCheckBox *cBox = new QCheckBox();
			Qt::CheckState state = Qt::Unchecked;
			QStringList lst = mem3.value(i+1).split(",");

			if(lst.value(1) != "-1")
			{
				cBox->setTristate(true);
				if(lst.value(2) == val)
				{
					state = Qt::Checked;
				}
				else if(lst.value(1) == val)
				{
					state = Qt::PartiallyChecked;
				}
			}
			else
			{
				if(lst.value(2) == val)
				{
					state = Qt::Checked;
				}
			}

			cBox->setObjectName(QString::number(i+1));
			if(cBox->isTristate())
			{
				cBox->setCheckState(state);
			}
			else
			{
				cBox->setChecked(state);
			}
			cBox->setText(val);
			connect(cBox, SIGNAL(stateChanged(int)), this, SLOT(dataBoolWasModified(int)));
			items.append(cBox);
		}
		else if(curType == "counter")
		{
			QSpinBox *sBox = new QSpinBox();
			int rMin = mem3.value(i+1).section(',',0,0).toInt();
			int rStep = mem3.value(i+1).section(',',1,1).toInt();
			qint32 rMax = mem3.value(i+1).section(',',2,2).toLong();

			sBox->setRange(rMin,rMax);
			sBox->setSingleStep(rStep);
			sBox->setValue(val.toInt());
			sBox->setObjectName(QString::number(i+1));
			connect(sBox, SIGNAL(valueChanged(QString)), this, SLOT(dataStringWasModified(QString)));
			items.append(sBox);
		}
		else if(curType == "range")
		{
			QSpinBox *sBox = new QSpinBox();
			int rMin = mem3.value(i+1).section(',',0,0).toInt();
			int rStep = mem3.value(i+1).section(',',1,1).toInt();
			int rMax = mem3.value(i+1).section(',',2,2).toInt();

			sBox->setRange(rMin, rMax);
			sBox->setSingleStep(rStep);
			sBox->setObjectName(QString::number(i+1));
			sBox->setValue(val.toInt());
			connect(sBox, SIGNAL(valueChanged(QString)), this, SLOT(dataStringWasModified(QString)));
			items.append(sBox);
		}
		else if(curType == "timer")
		{
			// Displaying the time is bit more complicated. Scientific notation and all that jazz.
			QDoubleSpinBox *dsBox = new QDoubleSpinBox();
			int rMin = mem3.value(i+1).section(',',0,0).toInt();
			int rStep = mem3.value(i+1).section(',',1,1).toInt();
			qint64 rMax = mem3.value(i+1).section(',',2,2).toLongLong();

			dsBox->setDecimals(0);
			dsBox->setRange(rMin,rMax);
			dsBox->setSingleStep(rStep);
			dsBox->setValue(val.toDouble());
			dsBox->setObjectName(QString::number(i+1));
			connect(dsBox, SIGNAL(valueChanged(double)), this, SLOT(dataTimeWasModified(double)));
			items.append(dsBox);
		}
		else
		{
			// Usually these are "unused" or "unaccessed"... Usually.
			QLineEdit *lEdi =  new QLineEdit();
			lEdi->setText(val);
			lEdi->setObjectName(QString::number(i+1));
			connect(lEdi, SIGNAL(textEdited(QString)), this, SLOT(dataStringWasModified(QString)));
			items.append(lEdi);
		}

		// Entry "title" label
		QLabel *qLab = new QLabel();
		qLab->setText(QString(mem1.value(i+1)));
		qLab->setFrameStyle(QFrame::Box | QFrame::Plain);
		qLab->setFixedWidth(220);
		qLab->setFixedHeight(20);
		qLab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		info[i] = qLab;

		// Entry number
		QLabel *nLab = new QLabel();
		nLab->setText(QString::number(i+1).rightJustified(3,'0'));
		nLab->setAlignment(Qt::AlignCenter);
		nLab->setFrameStyle(QFrame::Box | QFrame::Plain);
		nLab->setFixedWidth(30);
		nLab->setFixedHeight(20);
		nLab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		numfo[i] = nLab;

		// Entry comment
		QTextBrowser *tBro = new QTextBrowser;
		tBro->setText(mem4.value(i+1));
		tBro->setFixedWidth(175);
		tBro->setFixedHeight(50);
		comment[i] = tBro;

		// Horizontal container for current row. Add all components in to the mix.
		QHBoxLayout *hLay = new QHBoxLayout;
		hLay->addWidget(comment[i]);
		hLay->addWidget(numfo[i]);
		hLay->addWidget(info[i]);
		hLay->addWidget(items[i]);

		// Finally, add a little label for the time, which gets converted to human-readable format
		if(curType == "timer")
		{
			QLabel *tLab = new QLabel();
			qint64 tim = val.toDouble();
			int hour = std::fmod(tim/108000, 60);
			int minute = std::fmod(tim/1800, 60);
			int second = std::fmod(tim/30, 60);
			tLab->setText( QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second));
			tLab->setObjectName("timeLabel");
			tLab->setFrameStyle(QFrame::Box | QFrame::Plain);
			tLab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
			hLay->addWidget(tLab);
		}

		// Add container to interface
		ui->contentLayout->addLayout(hLay);
	}
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
}

void MainWindow::displayInfo()
{
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

	int size = mem0.size();
	for(int i = 0; i < size; i++)
	{
		// It's better to store the value inside a variable rather than fetch the value each time it's needed.
		QString curType = mem2.value(i+1);
		QString val = mem0.value(i+1);
		if(curType == "bool")
		{
			QWidget *dummy = items[i];
			dummy->setProperty("text", val);
			dummy->setProperty("value", val.toInt());
			Qt::CheckState state = Qt::Unchecked;
			QStringList lst = mem3.value(i+1).split(",");

			if(lst.value(2) == val)
			{
				state = Qt::Checked;
			}
			else if(lst.value(1) == val)
			{
				state = Qt::PartiallyChecked;
			}

			if(dummy->property("isTristate") == true)
			{
				dummy->setProperty("checkState", state);
			}
			else
			{
				dummy->setProperty("checked", state);
			}

			if(!isModified)
			{
				dummy->setProperty("styleSheet", "");
			}

			if(edict.value("skipbool"))
			{
				comment[i]->setVisible(false);
				numfo[i]->setVisible(false);
				info[i]->setVisible(false);
				items[i]->setVisible(false);
			}
			else
			{
				comment[i]->setVisible(true);
				numfo[i]->setVisible(true);
				info[i]->setVisible(true);
				items[i]->setVisible(true);
			}
		}
		else if(curType == "counter")
		{
			QWidget *dummy = items.value(i);
			dummy->setProperty("value", val.toInt());
			if(!isModified)
			{
				dummy->setProperty("styleSheet", "");
			}

			if(edict.value("skipcount"))
			{
				comment[i]->setVisible(false);
				numfo[i]->setVisible(false);
				info[i]->setVisible(false);
				items[i]->setVisible(false);
			}
			else
			{
				comment[i]->setVisible(true);
				numfo[i]->setVisible(true);
				info[i]->setVisible(true);
				items[i]->setVisible(true);
			}
		}
		else if(curType == "range")
		{
			QWidget *dummy = items.value(i);
			dummy->setProperty("value", val.toInt());
			if(!isModified)
			{
				dummy->setProperty("styleSheet", "");
			}

			if(edict.value("skiprange"))
			{
				comment[i]->setVisible(false);
				numfo[i]->setVisible(false);
				info[i]->setVisible(false);
				items[i]->setVisible(false);
			}
			else
			{
				comment[i]->setVisible(true);
				numfo[i]->setVisible(true);
				info[i]->setVisible(true);
				items[i]->setVisible(true);
			}
		}
		else if(curType == "timer")
		{
			QWidget *dummy = items.value(i);
			dummy->setProperty("value", val.toDouble());
			if(!isModified)
			{
				dummy->setProperty("styleSheet", "");
			}
		}
		else
		{
			QWidget *dummy = items.value(i);
			dummy->setProperty("text", val);
			if(!isModified)
			{
				dummy->setProperty("styleSheet", "");
			}
			if(edict.value("skipnull") && curType == "unused")
			{
				comment[i]->setVisible(false);
				numfo[i]->setVisible(false);
				info[i]->setVisible(false);
				items[i]->setVisible(false);
			}
			else
			{
				comment[i]->setVisible(true);
				numfo[i]->setVisible(true);
				info[i]->setVisible(true);
				items[i]->setVisible(true);
			}
		}
		if(edict.value("skipdull"))
		{
			comment[i]->setVisible(false);
		}
		if(edict.value("skipnum"))
		{
			numfo[i]->setVisible(false);
		}
	}

	ui->contentLayout->update();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
}

void MainWindow::readSettings()
{
	// I use the word "edict" for user settings, because basically user is the law.
	qDebug() << "BEGIN readSettings()";
	QSettings config(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationDisplayName());
	qDebug() << "beginGroup(\"MainWindow\")";
	config.beginGroup("MainWindow");
		resize(config.value("size", QSize(MainWindow::minimumWidth(), MainWindow::minimumHeight())).toSize());
		qDebug() << QString("size:").leftJustified(20, '.') << config.value("size").toSize();
		move(config.value("position", QPoint((mResWidth/2) - (MainWindow::minimumWidth()/2), (mResHeight/2) - (MainWindow::minimumHeight()/2))).toPoint());
		qDebug() << QString("position:").leftJustified(20, '.') << config.value("position").toPoint();
		if(config.value("maximized", false).toString() == "true")
		{
			showMaximized();
		}
		qDebug() << QString("maximized: ").leftJustified(20, '.') << config.value("maximized").toString();
	config.endGroup();
	qDebug() << "beginGroup(\"Settings\")";
	config.beginGroup("Settings");
		edictFile = config.value("file", "file0").toString();
		qDebug() << QString("file:").leftJustified(20, '.') << edict.value("file");
		edictDir.setPath(config.value("directory", QDir::homePath() + "/AppData/Local/UNDERTALE/").toString());
		qDebug() << QString("dir:").leftJustified(20, '.') << edict.value("directory");
		edict["autofile"] = config.value("loadfile", 0).toInt();
		qDebug() << QString("autofile:").leftJustified(20, '.') << edict.value("loadfile");
		edict["autodir"] = config.value("loaddir", 0).toInt();
		qDebug() << QString("autodir:").leftJustified(20, '.') << edict.value("loaddir");
		edict["savenag"] = config.value("confirmsave", 1).toInt();
		qDebug() << QString("savenag:").leftJustified(20, '.') << edict.value("confirmsave");
		edict["totalrecall"] = config.value("rememberlastdir", 1).toInt();
		qDebug() << QString("totalrecall:").leftJustified(20, '.') << edict.value("rememberlastdir");
	config.endGroup();
	qDebug() << "beginGroup(\"Filters\")";
	config.beginGroup("Filters");
		edict["skipbool"] = config.value("skipboolean", 0).toInt();
		qDebug() << QString("skipbool:").leftJustified(20, '.') << edict.value("skipbool");
		edict["skipdull"] = config.value("skipcomment", 1).toInt();
		qDebug() << QString("skipdull:").leftJustified(20, '.') << edict.value("skipdull");
		edict["skipcount"] = config.value("skipcounter", 0).toInt();
		qDebug() << QString("skipcount:").leftJustified(20, '.') << edict.value("skipcount");
		edict["skipnum"] = config.value("skipnumber", 0).toInt();
		qDebug() << QString("skipnum:").leftJustified(20, '.') << edict.value("skipnum");
		edict["skiprange"] = config.value("skiprange", 0).toInt();
		qDebug() << QString("skiprange:").leftJustified(20, '.') << edict.value("skiprange");
		edict["skipnull"] = config.value("skipunused", 1).toInt();
		qDebug() << QString("skipnull:").leftJustified(20, '.') << edict.value("skipnull");
	config.endGroup();

	// A sprouting new feature...
	QSettings undertale(":/strings/undertale.ini", QSettings::IniFormat);
	inilist = undertale.allKeys();
	for(int i = 0; i < inilist.size(); i++)
	{
		// See? "edict" and "law".
		law.insert(inilist.at(i), undertale.value(inilist.value(i)).toString());
	}

#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	// At the moment using FOUR different files is more convenient than one really messy one.
	QFile infofile(":/strings/infofile");
	QFile typefile(":/strings/typefile");
	QFile rangefile(":/strings/rangefile");
	QFile dullfile(":/strings/dullfile");
	QTextStream buffer1(&infofile);
	QTextStream buffer2(&typefile);
	QTextStream buffer3(&rangefile);
	QTextStream buffer4(&dullfile);
	if(!infofile.open(QFile::ReadOnly | QFile::Text) || !typefile.open(QFile::ReadOnly | QFile::Text) || !rangefile.open(QFile::ReadOnly | QFile::Text) || !dullfile.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Application", QString("Cannot read file."));
		ui->statusBar->showMessage(QString("Loading file failed"));
		return;
	}
	else
	{
		int i = 0;
		while(!buffer1.atEnd())
		{
			buffer1.readLineInto(&mem1[++i]);
			buffer2.readLineInto(&mem2[i]);
			buffer3.readLineInto(&mem3[i]);
			buffer4.readLineInto(&mem4[i]);

			if(mem2.value(i) == "bool")
			{
				stats[0]++;
			}
			if(mem2.value(i) == "counter")
			{
				stats[1]++;
			}
			if(mem2.value(i) == "range")
			{
				stats[2]++;
			}
			if(mem2.value(i) == "unused")
			{
				stats[3]++;
			}
		}
	}

	infofile.close();
	typefile.close();
	rangefile.close();
	dullfile.close();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	workDir.setPath(QDir::currentPath());
	workFile = "file";
}

void MainWindow::writeSettings()
{
	qDebug() << "BEGIN writeSettings()";
	QSettings config(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName(), QApplication::applicationDisplayName());
	qDebug() << "beginGroup(\"MainWindow\")";
	config.beginGroup("MainWindow");
		if(!isMaximized())
		{
			qDebug() << QString("size:").leftJustified(20, '.') << size();
			config.setValue("size", size());
			qDebug() << QString("position:").leftJustified(20, '.') << pos();
			config.setValue("position", pos());
		}
		qDebug() << QString("maximized: ").leftJustified(20, '.') << isMaximized();
		config.setValue("maximized", isMaximized());
	config.endGroup();
	qDebug() << "beginGroup(\"Settings\")";
	config.beginGroup("Settings");
		qDebug() << QString("file:").leftJustified(20, '.') << edictFile;
		config.setValue("file", edictFile);
		qDebug() << QString("dir:").leftJustified(20, '.') << edictDir.path();
		config.setValue("directory", edictDir.path());
		qDebug() << QString("autofile:").leftJustified(20, '.') << edict.value("autofile");
		config.setValue("loadfile", edict.value("autofile"));
		qDebug() << QString("autodir:").leftJustified(20, '.') << edict.value("autodir");
		config.setValue("loaddir", edict.value("autodir"));
		qDebug() << QString("savenag:").leftJustified(20, '.') << edict.value("savenag");
		config.setValue("confirmsave", edict.value("savenag"));
		qDebug() << QString("totalrecall:").leftJustified(20, '.') << edict.value("totalrecall");
		config.setValue("rememberlastdir", edict.value("totalrecall"));
	config.endGroup();
	qDebug() << "beginGroup(\"Filters\")";
	config.beginGroup("Filters");
		qDebug() << QString("skipbool:").leftJustified(20, '.') << edict.value("skipbool");
		config.setValue("skipboolean", edict.value("skipbool"));
		qDebug() << QString("skipdull:").leftJustified(20, '.') << edict.value("skipdull");
		config.setValue("skipcomment", edict.value("skipdull"));
		qDebug() << QString("skipcount:").leftJustified(20, '.') << edict.value("skipcount");
		config.setValue("skipcounter", edict.value("skipcount"));
		qDebug() << QString("skipnum:").leftJustified(20, '.') << edict.value("skipnum");
		config.setValue("skipnumber", edict.value("skipnum"));
		qDebug() << QString("skiprange:").leftJustified(20, '.') << edict.value("skiprange");
		config.setValue("skiprange", edict.value("skiprange"));
		qDebug() << QString("skipnull:").leftJustified(20, '.') << edict.value("skipnull");
		config.setValue("skipunused", edict.value("skipnull"));
	config.endGroup();
}

void MainWindow::setupMenuBar()
{
	ui->menuConfig->setToolTipsVisible(true);
	ui->menuFile->setToolTipsVisible(true);
	ui->menuReset->setToolTipsVisible(true);

	ui->actionFileNew->setShortcut(QKeySequence::New);
	ui->actionFileNew->setStatusTip("Start fresh. Fresh sold separately.");
	ui->actionFileNew->setWhatsThis("This feature attempts to be similar to how the game makes a new save file.");

	ui->actionFileOpen->setShortcut(QKeySequence::Open);
	ui->actionFileOpen->setStatusTip("For opening files, dummy.");
	ui->actionFileOpen->setWhatsThis("Use your system's native filebrowser to conveniently select a pre-existing file.");

	ui->actionFileSave->setShortcut(QKeySequence::Save);
	ui->actionFileSave->setStatusTip("It would be a SHAME, if you lost all your work.");
	ui->actionFileSave->setWhatsThis("Saves your changes to currently open file, essentially replacing it.");

	ui->actionFileSaveAs->setShortcut(QKeySequence::SaveAs);
	ui->actionFileSaveAs->setStatusTip("It would be a greater SHAME, if you lost your original file.");
	ui->actionFileSaveAs->setWhatsThis("Use your system's native filebrowser to conveniently select name and location for your file.");

	ui->actionFileResetUndo->setStatusTip("Are you just going to throw away your progress?");
	ui->actionFileResetUndo->setWhatsThis("Restore data from a state when you first loaded your file.");

	ui->actionFileResetTrueReset->setStatusTip("What would Sans say about this?");
	ui->actionFileResetTrueReset->setWhatsThis("This will allow you to activate True Reset. Normally after certain conditions are met, player is presented with an option to reset.");

	ui->actionFileResetTransactionCancellation->setStatusTip("You felt your sins crawling on your back");
	ui->actionFileResetTransactionCancellation->setWhatsThis("Removes data and resets some values in an attempt to erase effects of Genodice Run and restore the \"Happy Ending\". If only you could erase your actions from your mind as easily.");

	ui->actionFileExit->setStatusTip("I will not stop you. However, when you leave... Please do not come back.");
	ui->actionFileExit->setWhatsThis("Closes this program. Same as pressing the \"X\" at the top corner.");

	ui->actionConfigUseEdictDir->setStatusTip(QString("Current Working directory: %1").arg(workDir.path()));
	ui->actionConfigUseEdictDir->setWhatsThis("Use \"Set Working Directory\" to specify your own directory, otherwise this program attempts to use the default UNDERTALE save location.");

	ui->actionConfigSetEdictDir->setStatusTip(QString("Appointed directory: %1").arg(edictDir.path()));
	ui->actionConfigSetEdictDir->setWhatsThis("Specify your own file for this program to load at startup, assuming you have enabled automatic file loading. By default this program attempts to use same file as the game is using.");

	ui->actionConfigUseEdictFile->setStatusTip(QString("Current Working file: %1").arg(workFile));
	ui->actionConfigUseEdictFile->setWhatsThis("Use \"Set Working File\" to specify your own directory, otherwise this program attempts to use the default UNDERTALE save location.");

	ui->actionConfigSetEdictFile->setStatusTip(QString("Appointed file: %1").arg(edictFile));
	ui->actionConfigSetEdictFile->setWhatsThis("Specify your own locations for this program to load at startup, assuming you have enabled automatic directory loading. By default this program attempts to use same location as the game is using.");

	ui->actionConfigSaveNag->setStatusTip("Give a warning if you are about to overwrite an existing file");
	ui->actionConfigSaveNag->setWhatsThis("Standard warning message will be displayed when an existing file is about to be overwritten via \"Save\" or \"Save As...\" functions.");

	ui->actionConfigTotalRecall->setStatusTip("Set working directory to last used directory");
	ui->actionConfigTotalRecall->setWhatsThis("Causes this program to use same directory that was used when either opening or saving a file. If this option is disabled, the starting directory is set to where this program is located.");

	ui->actionConfigFilterSkipBoolean->setStatusTip(QString("Skip %1 boolean entries").arg(stats[0]));
	ui->actionConfigFilterSkipBoolean->setWhatsThis("Boolean can be either true (1) or false (0). For some reason this time dome boolean entries has multiple values.");

	ui->actionConfigFilterSkipComments->setStatusTip("Skip 549 comment entries");
	ui->actionConfigFilterSkipComments->setWhatsThis("Comments are there to explain in more detail what each entry means. And to clutter the user interface.");

	ui->actionConfigFilterSkipCounter->setStatusTip(QString("Skip %1 counter entries").arg(stats[1]));
	ui->actionConfigFilterSkipCounter->setWhatsThis("Counters usually start from 0 and only go up. Like Kill count or number of dogs encountered.");

	ui->actionConfigFilterSkipRange->setStatusTip(QString("Skip %1 range entries").arg(stats[2]));
	ui->actionConfigFilterSkipRange->setWhatsThis("Range should be a freely moving value within a certain range of values. Like range between -10 and 10.");

	ui->actionConfigFilterSkipNull->setStatusTip(QString("Skip %1 basically useless entries").arg(stats[3]));
	ui->actionConfigFilterSkipNull->setWhatsThis("Savefile contains lots of unused and unaccesed entries, due to cut content or nature of how the software handles savefiles. Skipping entries that are know to be essentially useless can make viewing and editing the file easier.");

	ui->actionConfigUseEdictDir->setChecked(edict.value("autodir"));
	ui->actionConfigUseEdictFile->setChecked(edict.value("autofile"));
	ui->actionConfigTotalRecall->setChecked(edict.value("totalrecall"));
	ui->actionConfigSaveNag->setChecked(edict.value("savenag"));
	ui->actionConfigFilterSkipBoolean->setChecked(edict.value("skipbool"));
	ui->actionConfigFilterSkipComments->setChecked(edict.value("skipdull"));
	ui->actionConfigFilterSkipCounter->setChecked(edict.value("skipcount"));
	ui->actionConfigFilterSkipNull->setChecked(edict.value("skipnull"));
	ui->actionConfigFilterSkipRange->setChecked(edict.value("skiprange"));
	ui->actionConfigFilterSkipNumber->setChecked(edict.value("skipnum"));

	if(edict.value("autodir"))
	{
		workDir = edictDir;
		if(!workDir.exists())
		{
			QMessageBox::warning(this, "Application", QString("Cannot access directory %1:\n%2.").arg(workDir.path(), "Directory does not exist"));
			workDir.setPath(QDir::currentPath());
		}
	}
	if(edict.value("autofile"))
	{
		workFile = edictFile;
		if(QFile::exists(workDir.filePath(workFile)))
		{
			loadFile(workDir, workFile);
		}
		else
		{
			QMessageBox::warning(this, "Application", QString("Cannot access file %1:\n%2.").arg(workFile, "File does not exist"));
			workFile.clear();
		}
	}
}

bool MainWindow::castWork()
{
	if (isModified)
	{
		QMessageBox confirm;
		confirm.setText("That's some really nice modifications.");
		confirm.setInformativeText("It would be a SHAME if something\n\"happened\" to them.");
		confirm.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		confirm.setDefaultButton(QMessageBox::Cancel);
		confirm.setIconPixmap(QPixmap(":/images/flowey.png"));
		int result = confirm.exec();
		switch(result)
		{
			case QMessageBox::Save:
			return on_actionFileSave_triggered();

			case QMessageBox::Cancel:
			return false;
		}
	}
	fileWasModified(0);
	return true;
}

void MainWindow::loadFile(const QDir &fileDir, const QString &fileName)
{
	qDebug() << "BEGIN loadFile(" << fileDir.path() << ", " << fileName << ")";
	QFile file(fileDir.filePath(fileName));
	if(!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Application", QString("Cannot read %1 in %2:\n%3.").arg(fileName, fileDir.path(), file.errorString()));
		ui->statusBar->showMessage(QString("Loading %1 in %2 failed").arg(fileName, fileDir.path()));
		return;
	}
	else
	{
	#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
	#endif
//		if(QFile::exists(fileDir.filePath("undertale.ini")))
//		{
//			inilist.clear();
//			QSettings utconf(QString(fileDir.filePath("undertale.ini")), QSettings::IniFormat);
//			inilist = utconf.allKeys();
//			for(int i = 0; i < inilist.size(); i++)
//			{
//				inivals.append(utconf.value(inilist.value(i)).toString());
//				qDebug() << "utconf[" << inilist.at(i) << "]:" << inivals.value(i);
//			}
//		}
		QTextStream buffer(&file);
		int i = 0;
		while(!buffer.atEnd())
		{
			buffer.readLineInto(&mem0[++i]);
			mem0[i] = mem0.value(i).simplified();
		}
		setWindowFilePath(fileDir.filePath(fileName));
		setWindowTitle(TITLELABEL);
		ui->statusBar->showMessage(QString("Loading %1 in %2 complete").arg(fileName, fileDir.path()));

		if(edict.value("totalrecall"))
		{
			workDir = fileDir;
		}
	}
	file.close();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
}

bool MainWindow::saveFile(const QDir &fileDir, const QString &fileName)
{
	qDebug() << "BEGIN saveFile(" << fileDir.path() << ", " << fileName << ")";
	if(QFile::exists(fileDir.filePath(fileName)) && edict.value("savenag"))
	{
		int result = QMessageBox::question(this, "Confirm Overwrite", QString("Do you want to overwrite %1?").arg(fileName), QMessageBox::Yes | QMessageBox::No);
		if(result == QMessageBox::No)
		{
			return false;
		}
	}
	QFile file(fileDir.filePath(fileName));
	if(!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Application", QString("Cannot read %1 in %2:\n%3.").arg(fileName, fileDir.path(), file.errorString()));
		ui->statusBar->showMessage(QString("Saving %1 in %2 failed").arg(fileName, fileDir.path()));
		return false;
	}
	else
	{
	#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
	#endif
		QTextStream buffer(&file);
		int size = mem0.size();
		for(int i = 1; i <= size; i++)
		{
			if(i == size)
			{
				buffer << mem0.value(i);
			}
			else
			{
				endl(buffer << mem0.value(i));
			}
		}
		file.close();
	#ifndef QT_NO_CURSOR
		QApplication::restoreOverrideCursor();
	#endif
		if(edict.value("totalrecall"))
		{
			workDir = fileDir;
		}
		fileWasModified(0);
		setWindowFilePath(fileDir.filePath(fileName));
		setWindowTitle(TITLELABEL);
		ui->statusBar->showMessage(QString("Saving %1 in %2 complete").arg(fileName, fileDir.path()));
	}
	return true;
}

void MainWindow::dataSliderWasModified(int number)
{
	qDebug() << "dataSliderWasModified(" << number << ")";
	int index = sender()->property("objectName").toInt();
	mem0[index] = QString::number(number);
	if(unitReady)
	{
		fileWasModified(1);
	}
}

void MainWindow::dataStringWasModified(QString string)
{
	qDebug() << "dataStringWasModified(" << string << ")";
	int index = sender()->property("objectName").toInt();
	mem0[index] = string;
	if(unitReady)
	{
		fileWasModified(1);
	}
}

void MainWindow::dataTimeWasModified(double number)
{
	qDebug() << "dataTimeWasModified(" << number << ")";
	QString string = QString::number(number);
	int index = sender()->property("objectName").toInt();
	mem0[index] = string;

	QLabel *timeLabel = this->findChild<QLabel *>("timeLabel");
	qint64 tim = mem0.value(index).toDouble();
	int hour = std::fmod(tim/108000, 60);
	int minute = std::fmod(tim/1800, 60);
	int second = std::fmod(tim/30, 60);
	timeLabel->setText( QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second));
	if(unitReady)
	{
		fileWasModified(1);
	}
}

void MainWindow::dataBoolWasModified(int number)
{
	qDebug() << "USE dataBoolWasModified(bool " << number << ")";
	QObject *dummy = sender();
	int index = dummy->property("objectName").toInt();
	int fst = mem3.value(index).section(',',0,0).toInt();
	int snd = mem3.value(index).section(',',1,1).toInt();
	int trd = mem3.value(index).section(',',2,2).toInt();
	switch(number)
	{
		case 0:
			number = fst;
		break;

		case 1:
			number = snd;
		break;

		case 2:
			number = trd;
		break;
	}

	mem0[index] = QString::number(number);
	dummy->setProperty("text", QString::number(number));
	if(unitReady)
	{
		fileWasModified(1);
	}
}

void MainWindow::fileWasModified(bool mode)
{
	qDebug() << "BEGIN documentWasModified(bool " << mode << ")";
	QObject *dummy = sender();
	if(mode)
	{
		isModified = true;
		if(dummy != NULL)
		{
			dummy->setProperty("styleSheet", "background-color: yellow");
		}
	}
	else
	{
		isModified = false;
	}
	setWindowModified(isModified);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	qDebug() << "BEGIN closeEvent(QCloseEvent " << &event << ")";
	if (castWork())
	{
		writeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionFileNew_triggered()
{
	unitReady = false;
	if(castWork())
	{
		QString cName = mem0.value(1);
		int fun = qrand()%((100 + 1) - 1) + 1;
		qDebug() << "cName: " << cName << ", fun: " << fun;
		workFile.clear();
		workFile = "file";
		setWindowFilePath(workFile);
		setWindowTitle(TITLELABEL);

		unitReady = false;
		QFile freshFile(":/strings/freshfile");
		if(!freshFile.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, "Application", QString("Cannot generating a fresh file :\n%1.").arg(freshFile.errorString()));
			ui->statusBar->showMessage(QString("Generating a fresh file failed"));
			return;
		}
		else
		{
		#ifndef QT_NO_CURSOR
			QApplication::setOverrideCursor(Qt::WaitCursor);
		#endif
			QTextStream freshBuffer(&freshFile);
			int i = 0;
			while(!freshBuffer.atEnd())
			{
				freshBuffer.readLineInto(&mem0[++i]);
				mem0[i] = mem0.value(i).simplified();
			}
			freshFile.close();
		#ifndef QT_NO_CURSOR
			QApplication::restoreOverrideCursor();
		#endif

			ui->statusBar->showMessage(QString("Generating a fresh file complete"));
			unitReady = true;
		}
		mem0[1] = cName;
		mem0[36] = QString::number(fun);
		fileWasModified(1);
		displayInfo();
	}
	unitReady = true;
}

void MainWindow::on_actionFileOpen_triggered()
{
	unitReady = false;
	if (castWork())
	{
		QDir targetDir;
		QString targetFile = QFileDialog::getOpenFileName(this,"Select a file", workDir.path());
		if (!targetFile.isEmpty())
		{
			workFile = targetFile.section("/", -1);
			targetFile.chop(workFile.size());
			targetDir.setPath(targetFile);
			loadFile(targetDir, workFile);
		}
	}
	fileWasModified(0);
	displayInfo();
	unitReady = true;
}

bool MainWindow::on_actionFileSave_triggered()
{
	unitReady = false;
	if (workFile.isEmpty() || !unitReady)
	{
		return on_actionFileSaveAs_triggered();
	}
	else
	{
		return saveFile(workDir, workFile);
	}
	unitReady = true;
	return false;
}

bool MainWindow::on_actionFileSaveAs_triggered()
{
	unitReady = false;
	QDir targetDir;
	QString filter = "";
	QString targetFile = QFileDialog::getSaveFileName(this, "Save As...", workDir.path() + "/" + workFile, "", &filter, QFileDialog::DontConfirmOverwrite);
	if(!targetFile.isEmpty())
	{
		workFile = targetFile.section("/", -1);
		targetFile.chop(workFile.size());
		targetDir.setPath(targetFile);

		return saveFile(targetDir, workFile);
	}
	unitReady = true;
	return false;
}

void MainWindow::on_actionFileExit_triggered()
{
	if(castWork())
	{
		this->close();
	}

}

void MainWindow::on_actionConfigUseEdictDir_toggled(bool arg1)
{
	edict["autodir"] = arg1;
}

void MainWindow::on_actionConfigSetEdictDir_triggered()
{
	QDir targetDir = QFileDialog::getExistingDirectory(this, "Select Directory", workDir.path(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks | QFileDialog::DontUseCustomDirectoryIcons);
	if(targetDir.path() != ".")
	{
		edictDir = targetDir;
	}
	ui->actionConfigUseEdictDir->setStatusTip(QString("Appointed directory: %1").arg(edictDir.path()));
	ui->actionConfigSetEdictDir->setStatusTip(QString("Current Working directory: %1").arg(edictDir.path()));
}

void MainWindow::on_actionFileResetUndo_triggered()
{
	// Is supposed to reset changes made to a file. Same as trying to open a new file and discarding changes.
}

void MainWindow::on_actionConfigSaveNag_toggled(bool arg1)
{
	edict["savenag"] = arg1;
}

void MainWindow::on_actionFileResetTrueReset_triggered()
{
	// Intended to have same effect as the in-game "True Reset"

}

void MainWindow::on_actionFileResetTransactionCancellation_triggered()
{
	// For undoing certain SOUL transaction with a certain FALLEN CHILD
}

void MainWindow::on_actionConfigUseEdictFile_toggled(bool arg1)
{
	edict["autofile"] = arg1;
}

void MainWindow::on_actionConfigSetEdictFile_triggered()
{
	QString targetFile = QFileDialog::getOpenFileName(this,"Select a file", workDir.path());
	if(!targetFile.isEmpty())
	{
		edictFile = targetFile.section("/", -1);
	}
	ui->actionConfigUseEdictFile->setStatusTip(QString("Appointed file: %1").arg(edictFile));
	ui->actionConfigSetEdictFile->setStatusTip(QString("Current Working file: %1").arg(edictFile));
}

void MainWindow::on_actionConfigTotalRecall_toggled(bool arg1)
{
	edict["totalrecall"] = arg1;
}

void MainWindow::on_actionConfigFilterSkipBoolean_toggled(bool arg1)
{
	edict["skipbool"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}

void MainWindow::on_actionConfigFilterSkipComments_toggled(bool arg1)
{
	edict["skipdull"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}

void MainWindow::on_actionConfigFilterSkipCounter_toggled(bool arg1)
{
	edict["skipcount"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}

void MainWindow::on_actionConfigFilterSkipNull_toggled(bool arg1)
{
	edict["skipnull"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}

void MainWindow::on_actionConfigFilterSkipRange_toggled(bool arg1)
{
	edict["skiprange"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}

void MainWindow::on_actionConfigFilterSkipNumber_toggled(bool arg1)
{
	edict["skipnum"] = arg1;
	if(unitReady)
	{
		displayInfo();
	}
}
