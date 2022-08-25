#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QCloseEvent>
#include <QDateTime>
#include <QDesktopServices>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QScrollBar>
#include <QSettings>
#include <QStandardPaths>
#include <QStyleFactory>
#include <QTextStream>
#include <QTimer>

#include <QDebug>

#include "src/core/mainwindow.h"
#include "src/core/dialogs.h"
#include "src/core/pages.h"
#include "src/helpers.h"
#include "src/filedownloader.h"

// icon (64) + left padding (20) + right padding (20) + scroll bar (16)
#define ICONS_WIDTH 120

#define SAVELEN 549

#define FETCH_DAILY 1
#define FETCH_WEEKLY 7
#define FETCH_MONTHLY 30
#define FETCH_BIANNUALLY 180

#define SAVED_FILE 1U
#define SAVED_INI 2U

#define INDEX_FILE 0
#define INDEX_INI 1

MainWindow* MainWindow::instance = nullptr;
bool MainWindow::exists = true;
QMultiHash<int, CustomEditor *> MainWindow::editors;
QStringList MainWindow::saveData;
QStringList MainWindow::originalFile;
QMultiHash<QString, CustomEditor *> MainWindow::iniEditors;
QHash<QString, QVariant> MainWindow::iniData;
QHash<QString, QVariant> MainWindow::originalIni;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	instance = this;

#if defined(Q_OS_LINUX)
	workDir = QDir::homePath() + QStringLiteral("/.config/UNDERTALE");
	storeDir = QDir::homePath() + QStringLiteral("/.config/%1/%2").arg(QApplication::organizationName(), QApplication::applicationName());
#elif defined(Q_OS_MACOS)
	workDir = QDir::homePath() + QStringLiteral("/Library/Application Support/com.tobyfox.undertale");
	storeDir = QDir::homePath() + QStringLiteral("/Library/Preferences/%1/%2").arg(QApplication::organizationName(), QApplication::applicationName());
#else
	workDir = QDir::homePath() + QStringLiteral("/AppData/Local/UNDERTALE");
	storeDir = QDir::homePath() + QStringLiteral("/AppData/Local/%1/%2").arg(QApplication::organizationName(), QApplication::applicationName());
#endif
	QDir().mkpath(storeDir); // A "hacky" way to make sure the "storage" is ready

	setWindowTitle(QStringLiteral("%1 (%2)").arg(QApplication::applicationName(), QApplication::applicationVersion()));
	setObjectName(QStringLiteral("mainwindow"));

	// Check for the user settings and load them if possible
	QFile file(storeDir + QStringLiteral("/config.json"));
	if (file.exists())
	{
		if (file.open(QFile::Text | QFile::ReadOnly))
		{
			const QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
			const QJsonObject updateJson = json.value(QStringLiteral("update")).toObject();
			const QJsonObject optionsJson = json.value(QStringLiteral("options")).toObject();

			fetchDelay = updateJson.value(QStringLiteral("delay")).toInt(7);
			fetchTime = updateJson.value(QStringLiteral("time")).toInteger(QDateTime::currentSecsSinceEpoch());
			fetchVersion = updateJson.value(QStringLiteral("version")).toString(QStringLiteral("0.0.0.0"));
			fetchMessage = updateJson.value(QStringLiteral("message")).toString(QStringLiteral("No details for this update were found"));

			toggleOptions.data = static_cast<quint32>(optionsJson.value(QStringLiteral("toggles")).toInt(TOGGLE_DARKMODE));
		}
	}

	// Dark Mode shenanigans
	QColor baseColor(QStringLiteral("#32383D"));
	QColor complementColor(QStringLiteral("#202529"));
	QColor disabledColor(QStringLiteral("#4C555C"));
	QColor highlightColor(QStringLiteral("#009BFF"));
	QColor linkColor(QStringLiteral("#009BFF"));

	lightPalette = QApplication::palette(); // Easier to store the default palette and use that as "light mode"
	darkPalette = QApplication::palette(); // To avoid conflicts, it's better to copy the current palette as base for dark mode

	darkPalette.setColor(QPalette::Active, QPalette::Button, disabledColor.darker());
	darkPalette.setColor(QPalette::AlternateBase, complementColor);
	darkPalette.setColor(QPalette::Base, baseColor);
	darkPalette.setColor(QPalette::Button, complementColor);
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledColor);
	darkPalette.setColor(QPalette::Disabled, QPalette::Light, complementColor);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, disabledColor);
	darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, disabledColor);
	darkPalette.setColor(QPalette::Highlight, highlightColor);
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);
	darkPalette.setColor(QPalette::Link, linkColor);
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::ToolTipBase, highlightColor);
	darkPalette.setColor(QPalette::ToolTipText, Qt::white);
	darkPalette.setColor(QPalette::Window, complementColor);
	darkPalette.setColor(QPalette::WindowText, Qt::white);

	// Fill in the default data to prevent errors
	saveData.fill(QStringLiteral("0"), SAVELEN + 1);
	saveData.replace(0, QStringLiteral("null")); // Placeholder for unused data. mostly for debugging
	saveData.replace(1, QStringLiteral("Chara")); // Player name
	saveData.replace(2, QStringLiteral("1")); // Player level
	saveData.replace(3, QStringLiteral("20")); // Max HP
	saveData.replace(4, QStringLiteral("20")); // EXP
	saveData.replace(5, QStringLiteral("10")); // AT stat
	saveData.replace(7, QStringLiteral("10")); // DF stat
	saveData.replace(9, QStringLiteral("4")); // SP stat
	saveData.replace(29, QStringLiteral("3")); // Weapon
	saveData.replace(30, QStringLiteral("4")); // Armor
	saveData.replace(36, QStringLiteral("100")); // "fun" value
	saveData.replace(331, QStringLiteral("14")); // Box slot 1 (Set to "Tough Glove")

	// File menu actions
	auto *openFileAction = new QAction(QStringLiteral("Open file"), this);
	auto *openIniAction = new QAction(QStringLiteral("Open ini"), this);
	auto *saveAction = new QAction(QStringLiteral("Save"), this);
	auto *saveAsAction = new QAction(QStringLiteral("Save As..."), this);
	auto *exitAction = new QAction(QStringLiteral("Exit"), this);
	// Options actions
	auto *showDebugAction = new QAction(QStringLiteral("Show Debug"), this);
	auto *showShrineAction = new QAction(QStringLiteral("Show Dog Shrine"), this);
	auto *toggleDarkTheme = new QAction(QStringLiteral("Use Dark Theme"), this);
	auto *fetchDaily = new QAction(QStringLiteral("Check Daily"));
	auto *fetchWeekly = new QAction(QStringLiteral("Check Weekly"));
	auto *fetchMonthly = new QAction(QStringLiteral("Check Monthly"));
	// About menu actions
	auto *showAboutAction = new QAction(QStringLiteral("About"), this);
	// Tool actions
	auto *yellowNamesAction = new QAction(QStringLiteral("Set monster names yellow"), this);

	// Create menus for the menu bar
	QMenu *fileMenu = menuBar()->addMenu(QStringLiteral("File"));
	fileMenu->addAction(openFileAction);
	fileMenu->addAction(openIniAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
	QMenu *optionMenu = menuBar()->addMenu(QStringLiteral("Options"));
	optionMenu->addAction(showDebugAction);
	optionMenu->addAction(showShrineAction);
	optionMenu->addAction(toggleDarkTheme);
	QMenu *fetchInterval = optionMenu->addMenu(QStringLiteral("Update Checking"));
	fetchInterval->addAction(fetchDaily);
	fetchInterval->addAction(fetchWeekly);
	fetchInterval->addAction(fetchMonthly);
	QMenu *toolsMenu = menuBar()->addMenu(QStringLiteral("Tools"));
	toolsMenu->addAction(yellowNamesAction);
	QMenu *helpMenu = menuBar()->addMenu(QStringLiteral("Help"));
	helpMenu->addAction(showAboutAction);

	// Create the main list menu
	icons = new QListWidget();
	icons->setViewMode(QListWidget::IconMode);
	icons->setIconSize(QSize(64, 64));
	icons->setSpacing(0);
	icons->setMaximumWidth(ICONS_WIDTH);
	icons->setMovement(QListView::Static);
	icons->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// Give the main list fancy icons
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-player")), QStringLiteral("Player"), icons));
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-toriel")), QStringLiteral("Bosses"), icons));
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-froggit")), QStringLiteral("Monsters"), icons));
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-locations")), QStringLiteral("Locations"), icons));
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-debug")), QStringLiteral("Debug"), icons));
	buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-shrine")), QStringLiteral("Dog Shrine"), icons));

	for (QListWidgetItem *item : buttons)
	{
		item->setSizeHint(QSize(104, 104)); // icon (64) + left padding (20) + right padding (20)
		item->setTextAlignment(Qt::AlignHCenter);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	icons->setRowHidden(4, !toggleOptions.option.showDebug);
	icons->setRowHidden(5, !toggleOptions.option.showShrine);

	// Create pages
	pages = new QStackedWidget();
	pages->addWidget(new PlayerPage());
	pages->addWidget(new BossesPage());
	pages->addWidget(new MonstersPage());
	pages->addWidget(new LocationsPage());
	pages->addWidget(new DebugPage());
	pages->addWidget(new ShrinePage());

	// Setup central widgets
	tabs = new QTabWidget();
	tabs->tabBar()->setDocumentMode(true);
	tabs->tabBar()->setExpanding(true);

	auto *fileWidget = new QWidget();
	auto *fileLayout = new QHBoxLayout();
	fileLayout->addWidget(icons);
	fileLayout->addWidget(pages);
	fileWidget->setLayout(fileLayout);
	tabs->addTab(fileWidget, QStringLiteral("file0"));
	tabs->setTabIcon(INDEX_FILE, floppy.at(0));
	tabs->setTabEnabled(INDEX_FILE, false); // Disable file tab by default. This will be enabled when a file is loaded

	auto *iniLayout = new QHBoxLayout();
	iniLayout->addWidget(new IniPage());
	auto *iniWidget = new QWidget();
	iniWidget->setLayout(iniLayout);
	tabs->addTab(iniWidget, QStringLiteral("undertale.ini"));
	tabs->setTabIcon(INDEX_INI, floppy.at(0));
	tabs->setTabEnabled(INDEX_INI, false); // Disable ini tab by default. This will be enabled when an ini is loaded

	// Connect actions to give them functionality
	connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
	connect(openIniAction, &QAction::triggered, this, &MainWindow::openIni);
	connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
	connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	connect(this, &MainWindow::enableControls, saveAction, &QAction::setEnabled);
	connect(this, &MainWindow::enableControls, saveAsAction, &QAction::setEnabled);

	connect(showDebugAction, &QAction::toggled, this, [this] (const bool checked) -> void {
		icons->setRowHidden(4, !checked);
		toggleOptions.option.showDebug = checked;
	});
	connect(showShrineAction, &QAction::toggled, this, [this] (const bool checked) -> void {
		icons->setRowHidden(5, !checked);
		toggleOptions.option.showShrine = checked;
	});
	connect(toggleDarkTheme, &QAction::toggled, this, [this] (const bool checked) -> void {
		QApplication::setPalette(checked ? darkPalette : lightPalette);
		toggleOptions.option.darkMode = checked;
		emit toggleDarkMode(checked);
	});
	connect(fetchDaily, &QAction::toggled, this, [this, fetchDaily, fetchWeekly, fetchMonthly] () -> void {
		// Block signals to prevent recursive activation
		const QSignalBlocker blockDaily(fetchDaily);
		const QSignalBlocker blockWeekly(fetchWeekly);
		const QSignalBlocker blockMonthly(fetchMonthly);

		fetchDaily->setChecked(true);
		fetchWeekly->setChecked(false);
		fetchMonthly->setChecked(false);

		fetchDelay = FETCH_DAILY;
	});
	connect(fetchWeekly, &QAction::toggled, this, [this, fetchDaily, fetchWeekly, fetchMonthly] () -> void {
		// Block signals to prevent recursive activation
		const QSignalBlocker blockDaily(fetchDaily);
		const QSignalBlocker blockWeekly(fetchWeekly);
		const QSignalBlocker blockMonthly(fetchMonthly);

		fetchDaily->setChecked(false);
		fetchWeekly->setChecked(true);
		fetchMonthly->setChecked(false);

		fetchDelay = FETCH_WEEKLY;
	});
	connect(fetchMonthly, &QAction::toggled, this, [this, fetchDaily, fetchWeekly, fetchMonthly] () -> void {
		// Block signals to prevent recursive activation
		const QSignalBlocker blockDaily(fetchDaily);
		const QSignalBlocker blockWeekly(fetchWeekly);
		const QSignalBlocker blockMonthly(fetchMonthly);

		fetchDaily->setChecked(false);
		fetchWeekly->setChecked(false);
		fetchMonthly->setChecked(true);

		fetchDelay = FETCH_MONTHLY;
	});
	connect(this, &MainWindow::enableTools, yellowNamesAction, &QAction::setEnabled);
	connect(yellowNamesAction, &QAction::triggered, this, [this] () -> void {
		auto *yellowNamesDialog = new YellowNamesDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
		yellowNamesDialog->setAttribute(Qt::WA_DeleteOnClose, true); // This is important. It prevents multiple dialog windows from being stored in memory
		yellowNamesDialog->show();
	});
	connect(showAboutAction, &QAction::triggered, this, [this] () -> void {
		auto *about = new AboutDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
		about->setAttribute(Qt::WA_DeleteOnClose, true); // This is important. It prevents multiple dialog windows from being stored in memory
		about->show();
	});
	connect(icons, &QListWidget::currentRowChanged, this, [this] (const int currentRow) -> void {
		pages->setCurrentIndex(currentRow);
	});

	// Final setup tasks
	showDebugAction->setCheckable(true);
	showShrineAction->setCheckable(true);
	toggleDarkTheme->setCheckable(true);
	fetchDaily->setCheckable(true);
	fetchWeekly->setCheckable(true);
	fetchMonthly->setCheckable(true);

	// These can't be enabled without an open file
	saveAction->setEnabled(false);
	saveAsAction->setEnabled(false);
	yellowNamesAction->setEnabled(false);

	// Customization options
	fetchDaily->setChecked(fetchDelay == FETCH_DAILY);
	fetchWeekly->setChecked(fetchDelay == FETCH_WEEKLY);
	fetchMonthly->setChecked(fetchDelay == FETCH_MONTHLY);
	toggleDarkTheme->setChecked(toggleOptions.option.darkMode);
	showDebugAction->setChecked(toggleOptions.option.showDebug);
	showShrineAction->setChecked(toggleOptions.option.showShrine);

	setCentralWidget(tabs);
	icons->setCurrentRow(0);
#ifdef QT_DEBUG
	// Immediately open files to speedup testing
	iniPath = QStringLiteral("DEBUG");
	filePath = QStringLiteral("DEBUG");
	openIni();
	openFile();
#endif
	setMinimumSize(768, 576); // Roughly the size of an old PAL screen. This is design "restriction" forces the interface to be more compact
	resize(768, 576);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (!isSaved(SAVED_FILE | SAVED_INI))
	{
		event->ignore();
		return;
	}

	QFile storage(storeDir + QStringLiteral("/config.json"));
	if (storage.open(QFile::Text | QFile::ReadWrite))
	{
		QJsonObject optionsJson = {
			{ QStringLiteral("toggles"), static_cast<qint32>(toggleOptions.data) }
		};
		QJsonObject updateJson = {
			{ QStringLiteral("delay"), fetchDelay },
			{ QStringLiteral("message"), fetchMessage },
			{ QStringLiteral("time"), fetchTime },
			{ QStringLiteral("version"), fetchVersion }
		};

		QJsonObject json = {
			{ QStringLiteral("options"), optionsJson },
			{ QStringLiteral("update"), updateJson }
		};

		storage.resize(0);
		storage.write(QJsonDocument::fromVariant(json.toVariantMap()).toJson(QJsonDocument::Indented));
	}

	exists = false;
	event->accept();
}

void MainWindow::showEvent(QShowEvent *event)
{
	QMainWindow::showEvent(event); // Add this just in case Qt changes the showEvent behavior in the future

	bool shouldFetch = false; // Assume we don't need to check for an update
	const QDateTime fetched = QDateTime::fromSecsSinceEpoch(fetchTime);
	const qint64 daysPassed = fetched.daysTo(QDateTime::currentDateTime());
	if (daysPassed > fetchDelay) // This is "close enough" to prevent the tool from checking during every start
	{
		shouldFetch = !isRemoteNewer(QApplication::applicationVersion(), fetchVersion); // If the "stored" version is newer, we can skip online check
		if (daysPassed > FETCH_BIANNUALLY) // Check anyway if six months have passed
		{
			shouldFetch = true;
		}

		if (!shouldFetch)
		{
			qDebug() << fetchDelay << "day(s)" << "has/have passed since the last prompt";
			QTimer::singleShot(10, this, &MainWindow::showVersionPrompt); // A short delay should get the main window visible and center the prompt
		}
	}

	if (shouldFetch)
	{
#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

#ifdef QT_DEBUG
		// Test version fetching with a local version.json in "home path"
		const QUrl url(QStringLiteral("file://") + QDir::homePath() + QStringLiteral("/version.json"));
#else
		const QUrl url(QStringLiteral("https://raw.githubusercontent.com/Cofeiini/UndertaleSaveEditor/master/version.json"));
#endif
		auto *downloader = new FileDownloader(url, this); // Downloader will handle deleting itself, so a pointer is fine here
		connect(downloader, &FileDownloader::downloaded, this, &MainWindow::readDownloadedData);
	}
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
}

void MainWindow::changeEvent(QEvent *event)
{
	QWidget::changeEvent(event);
}

void MainWindow::fileModified(const bool modified)
{
	const QString obj = sender() ? sender()->objectName() : objectName();
	const int opt = (modified << 1) | changedEntries.contains(obj);
	switch (opt)
	{
		// case 0b00: // Not modified and not found. Usually this is reset
		case 0b11: // Modified and found. Should skip repeat entry
		{
			return;
		}

		case 0b01: // Not modified and found. Should remove the entry
		{
			changedEntries.removeAll(obj);
			break;
		}

		case 0b10: // Modified and not found. Should add the entry
		{
			changedEntries.append(obj);
			break;
		}
	}

	const quint8 value = !changedEntries.isEmpty();
	bitChange<quint8>(isModified, value, SAVED_FILE);
	tabs->setTabIcon(INDEX_FILE, floppy.at(value));
}

void MainWindow::iniModified(const bool changed)
{
	const QString obj = sender() ? sender()->objectName() : objectName();
	const int opt = (changed << 1) | changedIniEntries.contains(obj);
	switch (opt)
	{
		// case 0b00: // Not modified and not found. Usually this is reset
		case 0b11: // Modified and found. Should skip repeat entry
		{
			return;
		}

		case 0b01: // Not modified and found. Should remove the entry
		{
			changedIniEntries.removeAll(obj);
			break;
		}

		case 0b10: // Modified and not found. Should add the entry
		{
			changedIniEntries.append(obj);
			break;
		}
	}

	const quint8 value = !changedIniEntries.isEmpty();
	bitChange<quint8>(isModified, value, SAVED_INI);
	tabs->setTabIcon(INDEX_INI, floppy.at(value));
}

void MainWindow::openFile()
{
	if (isSaved(SAVED_FILE))
	{
#ifdef QT_DEBUG
		if (filePath.compare(QStringLiteral("DEBUG")) == 0)
		{
			filePath = workDir + QStringLiteral("/file0");
		}
		else
#endif
		{
			const QString path = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), workDir, QStringLiteral("Save file (file*);;All Files (*)"));
			if (path.isEmpty())
			{
				return; // The user canceled the operation
			}
			filePath = path;
		}
		workDir = QFileInfo(filePath).dir().absolutePath();

		QFile file(filePath);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox prompt(this);
			prompt.setWindowTitle(QApplication::applicationName());
			prompt.setText(QStringLiteral("Cannot read file %1").arg(QDir::toNativeSeparators(filePath)));
			prompt.setDetailedText(file.errorString());
			prompt.setIcon(QMessageBox::Critical);
			prompt.exec();

			return;
		}

#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
		QTextStream in(&file);
		in.seek(0);
		for (int i = 1; i < SAVELEN; ++i)
		{
			saveData.replace(i, in.readLine().trimmed());
		}
		saveData.replace(SAVELEN, QString::number(static_cast<quint64>(in.readLine().trimmed().toDouble())));
		originalFile = saveData; // Make a copy for the "data changed" indicators
#ifndef QT_NO_CURSOR
		QApplication::restoreOverrideCursor();
#endif
		tabs->setTabEnabled(INDEX_FILE, true);
		tabs->setTabText(INDEX_FILE, QFileInfo(filePath).fileName());
		tabs->setCurrentIndex(INDEX_FILE);

		changedEntries.clear();

		emit updateWidgets();
		emit enableControls(true);
		emit enableTools(true);
	}
}

void MainWindow::openIni()
{
	if(isSaved(SAVED_INI))
	{
#ifdef QT_DEBUG
		if (iniPath.compare(QStringLiteral("DEBUG")) == 0)
		{
			iniPath = workDir + QStringLiteral("/undertale.ini");
		}
		else
#endif
		{
			const QString path = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), workDir, QStringLiteral("Ini File (*.ini);;All Files (*)"));
			if (path.isEmpty())
			{
				return;
			}
			iniPath = path;
		}
		workDir = QFileInfo(iniPath).dir().absolutePath();

		QSettings iniRead(iniPath, QSettings::IniFormat);
		for (const QString &item : iniRead.allKeys())
		{
			iniData.insert(item, iniRead.value(item));
		}
		originalIni = iniData;

		tabs->setTabEnabled(INDEX_INI, true);
		tabs->setTabText(INDEX_INI, QFileInfo(iniPath).fileName());
		tabs->setCurrentIndex(INDEX_INI);

		emit updateIniWidgets();
		emit enableControls(true);
	}
}

void MainWindow::saveFile()
{
	switch (tabs->currentIndex())
	{
		case INDEX_FILE:
		{
			writeFile();
			break;
		}
		case INDEX_INI:
		{
			writeIni();
			break;
		}
	}
}

void MainWindow::saveFileAs()
{
	const int fileIndex = tabs->currentIndex();

	const QString filter = (fileIndex == INDEX_FILE) ? QStringLiteral("Save file (file*);;All Files (*)") : QStringLiteral("Ini File (*.ini);;All Files (*)");
	QFileDialog dialog(this, QStringLiteral("Select where to save your file"), workDir, filter);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setFileMode(QFileDialog::AnyFile);
	if (dialog.exec() != QDialog::Accepted)
	{
		return; // The user canceled the operation
	}

	const QString path = dialog.selectedFiles().at(0);
	if (path.isEmpty())
	{
		return; // The user canceled the operation or a big error happened
	}

	const QFileInfo info(path);
	workDir = info.dir().absolutePath();
	tabs->setTabText(fileIndex, info.fileName());
	switch (fileIndex)
	{
		case INDEX_FILE:
		{
			filePath = path;
			break;
		}
		case INDEX_INI:
		{
			iniPath = path;
			break;
		}
	}

	saveFile();
}

void MainWindow::readDownloadedData(const QByteArray &data)
{
	QJsonObject json = QJsonDocument::fromJson(data).object();
	fetchVersion = json["version"].toString();
	fetchMessage = json["message"].toString();
	fetchTime = QDateTime::currentSecsSinceEpoch(); // We need to set the time here to account for the online check

#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif
	if(isRemoteNewer(QApplication::applicationVersion(), fetchVersion))
	{
		qDebug() << "Found an update";
		QTimer::singleShot(10, this, &MainWindow::showVersionPrompt); // 10 ms delay should give enough time for the main window to become visible in the "worst" case
	}
}

void MainWindow::showVersionPrompt()
{
	fetchTime = QDateTime::currentSecsSinceEpoch(); // Update the time to prevent the message from popping up every program launch

	const QString text = QStringLiteral("A new version is available");
	const QString info = QStringLiteral("Visit GitHub to download version %1?").arg(fetchVersion);
	const QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No;

	QMessageBox prompt(QMessageBox::Information, QApplication::applicationName(), text, buttons, this);
	prompt.setInformativeText(info);
	prompt.setDetailedText(fetchMessage);
	prompt.setModal(true);

	prompt.show(); // Force the prompt to show in order to update its geometry

	const QPoint center(qRound(static_cast<float>(prompt.geometry().width()) * 0.5f), qRound(static_cast<float>(prompt.geometry().height()) * 0.5f));
	prompt.move(geometry().center() - center); // Move the prompt to the center of the main window for convenience

	if (prompt.exec() == QMessageBox::Yes)
	{
		QDesktopServices::openUrl(QUrl(GitHub_Url + QStringLiteral("/releases")));
	}
}

void MainWindow::showWriteError(const QString &path, const QString &error)
{
	const QString text = QStringLiteral("Cannot write file %1").arg(QDir::toNativeSeparators(path));
	QMessageBox prompt(QMessageBox::Warning, QApplication::applicationName(), text, QMessageBox::Close, this);
	prompt.setDetailedText(error);
	prompt.exec();
}

auto MainWindow::isRemoteNewer(const QString &local, const QString &remote) -> bool
{
	QVector<int> lVec;
	lVec.reserve(4);
	for (const QString &i : local.split('.'))
	{
		bool ok = true;
		int n = i.toInt(&ok);
		if (!ok)
		{
			n = 0;
		}

		lVec.append(n);
	}
	lVec.resize(4); // Force the length to right size

	QVector<int> rVec;
	rVec.reserve(4);
	for (const QString &i : remote.split('.'))
	{
		bool ok = true;
		int n = i.toInt(&ok);
		if (!ok)
		{
			n = 0;
		}

		rVec.append(n);
	}
	rVec.resize(4); // Force the length to right size

	if (std::equal(lVec.begin(), lVec.end(), rVec.begin()))
	{
		return false; // This is a special case when the versions are the same
	}

	return std::lexicographical_compare(lVec.begin(), lVec.end(), rVec.begin(), rVec.end());
}

auto MainWindow::isSaved(const quint8 modifiedBits) -> bool
{
	if (!bitCheck(isModified, modifiedBits))
	{
		return true;
	}

	const QString text = QStringLiteral("Do you want to save your changes?");
	const QMessageBox::StandardButtons buttons = QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard;
	const QMessageBox::StandardButton result = QMessageBox::warning(this, QApplication::applicationName(), text, buttons, QMessageBox::Cancel);
	switch (result)
	{
		case QMessageBox::Save:
		{
			saveFile();
			return true;
		}

		case QMessageBox::Cancel:
		{
			return false;
		}

		default: // Discard
		{
			return true;
		}
	}
}

void MainWindow::writeFile()
{
	QFile file(filePath);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		showWriteError(filePath, file.errorString());
		return;
	}

#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	file.resize(0);
	QTextStream out(&file);
	for (int i = 1; i < SAVELEN; ++i)
	{
		out << saveData.at(i) << '\n';
	}
	out << QString::number(saveData.at(SAVELEN).toDouble(), 'g', 5);
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	originalFile = saveData;
	changedEntries.clear();

	emit updateWidgets();
	fileModified(false);
}

void MainWindow::writeIni()
{
	const QString tempPath = iniPath + QStringLiteral(".temp");
	QSettings iniOut(tempPath, QSettings::IniFormat);
	if(!iniOut.isWritable())
	{
		QString errorString = QStringLiteral("Unknown error");
		switch (iniOut.status())
		{
			case QSettings::NoError:
			{
				break; // Skip this and use the default message
			}

			case QSettings::AccessError:
			{
				errorString = QStringLiteral("Accessing the file failed");
				break;
			}

			case QSettings::FormatError:
			{
				errorString = QStringLiteral("Reading the file format failed");
				break;
			}
		}

		showWriteError(tempPath, errorString);
		return;
	}

	QFile file(iniPath);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		showWriteError(filePath, file.errorString());
		return;
	}

#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	QHash<QString, QVariant> tempData(iniData); // Make a copy to freely edit the data

	// The data needs quotes around it to be a valid save format
	iniOut.setValue(QStringLiteral("Name"), QStringLiteral("\"%1\"").arg(tempData.value(QStringLiteral("Name")).toString())); // Handle the only exception in the data separately
	tempData.remove(QStringLiteral("Name")); // Remove the exception to make iterating simpler

	QHash<QString, QVariant>::const_key_value_iterator iter = tempData.constKeyValueBegin();
	QHash<QString, QVariant>::const_key_value_iterator end = tempData.constKeyValueEnd();
	while (iter != end)
	{
		iniOut.setValue(iter->first, QStringLiteral("\"%1\"").arg(QString::number(iter->second.toDouble(), 'f', 6))); // Convert the data into the correct "double" format
		iter++;
	}
	iniOut.sync(); // Commit the changes to the file

	QFile tempFile(tempPath);
	if(!tempFile.open(QFile::ReadOnly | QFile::Text))
	{
		showWriteError(tempPath, tempFile.errorString());
		return;
	}

	file.resize(0);
	QTextStream input(&tempFile);
	QTextStream output(&file);

	while (!input.atEnd())
	{
		const QString line = input.readLine().remove('\\'); // Cleanup all backslashes
		if (!line.isEmpty())
		{
			output << line << '\n';
		}
	}

	tempFile.remove(); // Remember to clean up the temporary file
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	originalIni = iniData;
	changedIniEntries.clear();
	iniModified(false);
}
