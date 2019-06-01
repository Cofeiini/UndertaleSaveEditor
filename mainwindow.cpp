#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QSettings>
#include <QStandardPaths>
#include <QTextStream>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QPushButton>

#include "mainwindow.h"
#include "pages.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
#if defined(Q_OS_LINUX)
	workDir = QDir::homePath() + "/.config/UNDERTALE/";
#elif defined(Q_OS_MACOS)
	workDir = QDir::homePath() + "/Library/Application Support/com.tobyfox.undertale/";
#else
	workDir = QDir::homePath() + "/AppData/Local/UNDERTALE/";
#endif

	setWindowTitle(tr("%1 (v%2)").arg(QApplication::applicationName()).arg(QApplication::applicationVersion()));

	// create actions
	QAction *openFileAction = new QAction(tr("Open file"), this);
	connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

	QAction *openIniAction = new QAction(tr("Open ini"), this);
	connect(openIniAction, &QAction::triggered, this, &MainWindow::openIni);

	saveAction = new QAction(tr("Save"), this);
	saveAction->setEnabled(false);
	connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

	saveAsAction = new QAction(tr("Save As..."), this);
	saveAsAction->setEnabled(false);
	connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);

	QAction *exitAction = new QAction(tr("Exit"), this);
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	QAction *showDebugAction = new QAction(tr("Show Debug"), this);
	showDebugAction->setCheckable(true);
	showDebugAction->setChecked(false);
	connect(showDebugAction, &QAction::toggled, this, &MainWindow::showDebug);

	QAction *showDogAction = new QAction(tr("Show Dog Shrine"), this);
	showDogAction->setCheckable(true);
	showDogAction->setChecked(false);
	connect(showDogAction, &QAction::toggled, this, &MainWindow::showDog);

	QDialog *about = new QDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
	QAction *showAboutAction = new QAction(tr("About"), this);
	connect(showAboutAction, &QAction::triggered, about, &QDialog::show);

	// create menus for menubar
	QMenu *fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(openIniAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	QMenu *optionMenu = menuBar()->addMenu(tr("Options"));
	optionMenu->addAction(showDebugAction);
	optionMenu->addAction(showDogAction);

	menuBar()->addAction(showAboutAction);

	// create list menu
	icons.setViewMode(QListWidget::IconMode);
	icons.setIconSize(QSize(64, 64));
	icons.setMovement(QListView::Static);
	icons.setMaximumWidth(110); // 64 + 5 + 5 + 36
	icons.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	icons.setSpacing(5);
	connect(&icons,
			SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
			this, SLOT(changePage(QListWidgetItem *, QListWidgetItem *)));

	buttons.append(new QListWidgetItem(QIcon(":/images/ico_player.png"), tr("Player"), &icons));
	buttons.append(new QListWidgetItem(QIcon(":/images/ico_toriel.png"), tr("Bosses"), &icons));
	buttons.append(new QListWidgetItem(QIcon(":/images/ico_napstablook.png"), tr("Monsters"), &icons));
	buttons.append(new QListWidgetItem(QIcon(":/images/ico_savepoint.png"), tr("Locations"), &icons));
	buttons.append(new QListWidgetItem(QIcon(":/images/ico_debug.png"), tr("Debug"), &icons));
	buttons.append(new QListWidgetItem(QIcon(":/images/ico_dogshrine.png"), tr("Dog Shrine"), &icons));

	foreach (QListWidgetItem *item, buttons)
	{
		item->setTextAlignment(Qt::AlignHCenter);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	buttons.at(4)->setHidden(true);
	buttons.at(5)->setHidden(true);

	// create pages
	pages.addWidget(new PlayerPage(this));
	pages.addWidget(new BossesPage(this));
	pages.addWidget(new MonstersPage(this));
	pages.addWidget(new LocationsPage(this));
	pages.addWidget(new DebugPage(this));
	pages.addWidget(new DogPage(this));

	// setup central widget
	QWidget *fileWidget = new QWidget();
	QHBoxLayout *fileLayout = new QHBoxLayout(fileWidget);
	fileLayout->addWidget(&icons);
	fileLayout->addWidget(&pages);
	window.addTab(fileWidget, tr("file0"));
	window.setTabEnabled(0, false);
	window.setTabIcon(0, floppy[0]);

	QWidget *iniWidget = new QWidget();
	QHBoxLayout *iniLayout = new QHBoxLayout(iniWidget);
	iniLayout->addWidget(new INIPage(this));
	window.addTab(iniWidget, tr("undertale.ini"));
	window.setTabEnabled(1, false);
	window.setTabIcon(1, floppy[0]);

	// setup about dialog
	about->setModal(true);
	about->setMinimumSize(QSize(300, 170));
	about->setWindowTitle(tr("About %1").arg(QApplication::applicationName()));

	QPushButton *closeButton = new QPushButton(tr("Close"));
	connect(closeButton, &QPushButton::clicked, about, &QDialog::close);

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(closeButton);

	QLabel *aboutAppLabel = new QLabel(QString("<b>%1 %2</b>").arg(QApplication::applicationName()).arg(QApplication::applicationVersion()), about);
	aboutAppLabel->setAlignment(Qt::AlignCenter);
	QLabel *aboutProjectLabel = new QLabel("Project can be found at");
	QLabel *aboutLinkLabel = new QLabel("<a href=\"https://github.com/Cofeiini/UndertaleSaveEditor\">https://github.com/Cofeiini/UndertaleSaveEditor</a>");
	QLabel *aboutMadeByLabel = new QLabel("Made by <b>Cofeiini</b>.");
	QLabel *aboutThanksLabel = new QLabel("Thanks to <b>chaoskagami</b> and <b>Araraura</b>.");

	QVBoxLayout *aboutLayout = new QVBoxLayout(about);
	aboutLayout->addWidget(aboutAppLabel);
	aboutLayout->addWidget(aboutProjectLabel);
	aboutLayout->addWidget(aboutLinkLabel);
	aboutLayout->addStretch();
	aboutLayout->addWidget(aboutMadeByLabel);
	aboutLayout->addWidget(aboutThanksLabel);
	aboutLayout->addLayout(bottomLayout);

	// final setup tasks
	setCentralWidget(&window);
	icons.setCurrentItem(buttons.at(0));
	emit updateWidgets();
	fileModified(false);
	resize(1228, 690);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (checkIfFileSave())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void MainWindow::showEvent(QShowEvent *event)
{
	QMainWindow::showEvent(event);
	QUrl url("https://raw.githubusercontent.com/Cofeiini/UndertaleSaveEditor/master/version.json");
	downloader = new FileDownloader(url, this);
	connect(downloader, SIGNAL(downloaded()), this, SLOT(loadData()));
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
	if (!current)
	{
		current = previous;
	}
	pages.setCurrentIndex(icons.row(current));
}

void MainWindow::fileModified(bool value)
{
	isFileModified = value;
	window.setTabIcon(0, floppy[value]);
}

void MainWindow::iniModified(bool value)
{
	isIniModified = value;
	window.setTabIcon(1, floppy[value]);
}

void MainWindow::openFile()
{
	if (checkIfFileSave())
	{
		// choose file
		QString path = QFileDialog::getOpenFileName(this, tr("Open File"), workDir, QString("file (file*);;All Files (*)"));
		if (path.isEmpty())
		{
			return;
		}

		filePath = path;
		workDir = QFileInfo(path).dir().absolutePath();
		// open file
		QFile file(path);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, QApplication::applicationName(),
								 tr("Cannot read file %1:\n%2.")
									 .arg(QDir::toNativeSeparators(path),
										  file.errorString()));
			return;
		}

		QTextStream in(&file);

		// count lines to make sure the file is valid
		int count = 0;
		QString l;
		while (in.readLineInto(&l))
		{
			count++;
		}
		if (count < 549)
		{
			QMessageBox::warning(this, QApplication::applicationName(),
								 tr("File %1\n"
									"does not contain enough data or is "
									"incorrectly formated.")
									 .arg(QDir::toNativeSeparators(path)));
			return;
		}

#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
		// read file to memory
		in.seek(0);
		for (int i = 1; i <= 549; i++)
		{
			saveData.replace(i, in.readLine());
		}
#ifndef QT_NO_CURSOR
		QApplication::restoreOverrideCursor();
#endif
		window.setTabEnabled(0, true);
		window.setTabText(0, QFileInfo(path).fileName());
		window.setCurrentIndex(0);
		emit updateWidgets();
		fileModified(false);
	}
	saveAction->setEnabled(true);
	saveAsAction->setEnabled(true);
}

void MainWindow::openIni()
{
	if(checkIfIniSave())
	{
		// choose file
		QString path = QFileDialog::getOpenFileName(this, tr("Open File"), workDir, QString("Ini File (*.ini);;All Files (*)"));
		if (path.isEmpty())
		{
			return;
		}
		iniPath = path;
		workDir = QFileInfo(path).dir().absolutePath();

		// read ini
		QSettings iniRead(path, QSettings::IniFormat);
		foreach (QString item, iniRead.allKeys())
		{
			iniData.insert(item, iniRead.value(item));
		}

		window.setTabEnabled(1, true);
		window.setTabText(1, QFileInfo(path).fileName());
		window.setCurrentIndex(1);
		emit updateIniWidgets();
		iniModified(false);
	}
	saveAction->setEnabled(true);
	saveAsAction->setEnabled(true);
}

void MainWindow::saveFile()
{
	if(window.currentIndex() == 0)
	{
		writeFile();
	}
	else
	{
		writeIni();
	}
}

void MainWindow::saveFileAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setDirectory(workDir);
	if (dialog.exec() != QDialog::Accepted)
	{
		return;
	}

	QString path = dialog.selectedFiles().first();
	if (path.isEmpty())
	{
		return;
	}

	workDir = QFileInfo(path).dir().absolutePath();
	if (QFileInfo(path).completeSuffix().contains("ini"))
	{
		iniPath = path;
		window.setTabText(1, QFileInfo(path).fileName());
		writeIni();
	}
	else
	{
		filePath = path;
		window.setTabText(0, QFileInfo(path).fileName());
		writeFile();
	}
}

void MainWindow::loadData()
{
	QJsonObject json = QJsonDocument::fromJson(downloader->data).object();
	QString version = json["version"].toString();
	QStringList local = QApplication::applicationVersion().split('.');
	QStringList remote = version.split('.');

	int lArr[4] = {0}, rArr[4] = {0};
	int len = local.size();
	for (int i = 0; i < len; i++)
	{
		lArr[i] = local.at(i).toInt();
	}
	len = remote.size();
	for (int i = 0; i < len; i++)
	{
		rArr[i] = remote.at(i).toInt();
	}

	bool remoteIsNewer = std::lexicographical_compare(lArr, lArr + 4, rArr, rArr + 4);
	if(remoteIsNewer)
	{
		QMessageBox::information(this, tr("New version of this program is available"),
								 tr("Go to <a href=\"https://github.com/Cofeiini/UndertaleSaveEditor/releases\">https://github.com/Cofeiini/UndertaleSaveEditor/releases</a> to download version %1").arg(version),
								 QMessageBox::Ok);
	}
}

void MainWindow::showDebug(bool checked)
{
	buttons.at(4)->setHidden(!checked);
}

void MainWindow::showDog(bool checked)
{
	buttons.at(5)->setHidden(!checked);
}

bool MainWindow::checkIfFileSave()
{
	if (!isFileModified)
	{
		return true;
	}

	const QMessageBox::StandardButton ret = QMessageBox::warning(
		this, QApplication::applicationName(),
		tr("The file has been modified.\n"
		   "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	switch (ret)
	{
	case QMessageBox::Save:
		window.setCurrentIndex(0);
		saveFile();
		return true;
	case QMessageBox::Cancel:
		return false;
	default: // Discard
		return true;
	}
}

bool MainWindow::checkIfIniSave()
{
	if (!isIniModified)
	{
		return true;
	}

	const QMessageBox::StandardButton ret = QMessageBox::warning(
		this, QApplication::applicationName(),
		tr("The file has been modified.\n"
		   "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
	switch (ret)
	{
	case QMessageBox::Save:
		window.setCurrentIndex(1);
		saveFile();
		return true;
	case QMessageBox::Cancel:
		return false;
	default: // Discard
		return true;
	}
}

void MainWindow::writeFile()
{
	QFile file(filePath);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(
			this, QApplication::applicationName(),
			tr("Cannot write file %1:\n%2.")
				.arg(QDir::toNativeSeparators(filePath), file.errorString()));
		return;
	}

	QTextStream out(&file);

#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	for (int i = 1; i <= 549; i++)
	{
		out << saveData.at(i);
		if (i < 549)
		{
			out << "\n";
		}
	}
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
	fileModified(false);
}

void MainWindow::writeIni()
{
	QFile file(iniPath);
	if (!file.open(QFile::ReadWrite | QFile::Text))
	{
		QMessageBox::warning(
			this, QApplication::applicationName(),
			tr("Cannot write file %1:\n%2.")
				.arg(QDir::toNativeSeparators(iniPath), file.errorString()));
		return;
	}

	if (file.exists())
	{
		file.resize(0);
	}
	file.close();

	// this block is important!
	// it prevents QSettings from messing with the file during cleanup
	{
		QSettings out(iniPath, QSettings::IniFormat);
		if(out.isWritable())
		{
			foreach (QString item, iniData.keys())
			{
				if (item == "Name")
				{
					out.setValue(item, "\"" + iniData.value(item).toString() + "\"");
				}
				else
				{
					out.setValue(item, "\"" + QString::number(iniData.value(item).toDouble(), 'f', 6) + "\"");
				}
			}
		}
	}
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	// cleanup all backslashes from the file
	if(file.open(QFile::ReadWrite | QFile::Text))
	{
		QString s;
		QTextStream out(&file);
		while (!out.atEnd())
		{
			QString line = out.readLine().remove('\\');
			if (!line.isEmpty())
			{
				s.append(line + "\n");
			}
		}
		file.resize(0);
		out << s;
		file.close();
	}
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
	iniModified(false);
}
