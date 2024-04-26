#include "src/core/mainwindow.h"

#include "src/core/dialogs.h"
#include "src/core/pages.h"
#include "src/filedownloader.h"
#include "src/helpers.h"

#include <QAction>
#include <QBoxLayout>
#include <QCloseEvent>
#include <QDateTime>
#include <QDebug>
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

enum {
    SAVELEN = 549,

    FETCH_DAILY = 1,
    FETCH_WEEKLY = 7,
    FETCH_MONTHLY = 30,
    FETCH_BIANNUALLY = 180,

    SAVED_FILE = 1U,
    SAVED_INI = 2U,
};

MainWindow *MainWindow::instance = nullptr;
bool MainWindow::exists = true;
QMultiHash<int, CustomEditor *> MainWindow::editors;
QStringList MainWindow::saveData;
QStringList MainWindow::originalFile;
QStringList MainWindow::fileErrors;
QMultiHash<QString, CustomEditor *> MainWindow::iniEditors;
QHash<QString, QVariant> MainWindow::iniData;
QHash<QString, QVariant> MainWindow::originalIni;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    instance = this;

#if defined(Q_OS_LINUX)
    workDir = QStringLiteral("%1/.config/UNDERTALE").arg(QDir::homePath());
    storeDir = QStringLiteral("%1/.config/%2/%3").arg(QDir::homePath(), QApplication::organizationName(), QApplication::applicationName());
#elif defined(Q_OS_MACOS)
    workDir = QStringLiteral("%1/Library/Application Support/com.tobyfox.undertale").arg(QDir::homePath());
    storeDir = QStringLiteral("%1/Library/Preferences/%2/%3").arg(QDir::homePath(), QApplication::organizationName(), QApplication::applicationName());
#else
    workDir = QStringLiteral("%1/AppData/Local/UNDERTALE").arg(QDir::homePath());
    storeDir = QStringLiteral("%1/AppData/Local/%2/%3").arg(QDir::homePath(), QApplication::organizationName(), QApplication::applicationName());
#endif
    QDir().mkpath(storeDir); // A "hacky" way to make sure the "storage" is ready

    setWindowTitle(QStringLiteral("%1 (%2)").arg(QApplication::applicationName(), QApplication::applicationVersion()));
    setObjectName(QStringLiteral("mainwindow"));

    // Check for the user settings and load them if possible
    QFile file(QStringLiteral("%1/config.json").arg(storeDir));
    if (file.exists())
    {
        if (file.open(QFile::Text | QFile::ReadOnly))
        {
            const QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
            const QJsonObject updateJson = json.value(QStringLiteral("update")).toObject();
            const QJsonObject optionsJson = json.value(QStringLiteral("options")).toObject();

            fetchDelay = updateJson.value(QStringLiteral("delay")).toInt(FETCH_MONTHLY);
            fetchTime = updateJson.value(QStringLiteral("time")).toInteger(QDateTime::currentSecsSinceEpoch());
            fetchVersion = updateJson.value(QStringLiteral("version")).toString(QStringLiteral("0.0.0.0"));
            fetchMessage = updateJson.value(QStringLiteral("message")).toString(QStringLiteral("No details for this update were found"));

            toggleOptions.data = static_cast<quint32>(optionsJson.value(QStringLiteral("toggles")).toInt(1));
        }
    }

    // Light Mode shenanigans
    const QColor lightBaseColor(QStringLiteral("#FFFFFF"));
    const QColor lightComplementColor(QStringLiteral("#F2F2F2"));
    const QColor lightDisabledColor(QStringLiteral("#626262"));
    const QColor lightHighlightColor(QStringLiteral("#848484"));
    const QColor lightLinkColor(QStringLiteral("#009BFF"));

    lightPalette = QPalette();
    lightPalette.setColor(QPalette::Active, QPalette::Button, lightDisabledColor.lighter());
    lightPalette.setColor(QPalette::AlternateBase, lightComplementColor);
    lightPalette.setColor(QPalette::Base, lightBaseColor);
    lightPalette.setColor(QPalette::Button, lightComplementColor);
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::Disabled, QPalette::ButtonText, lightDisabledColor);
    lightPalette.setColor(QPalette::Disabled, QPalette::Light, lightComplementColor);
    lightPalette.setColor(QPalette::Disabled, QPalette::Text, lightDisabledColor);
    lightPalette.setColor(QPalette::Disabled, QPalette::WindowText, lightDisabledColor);
    lightPalette.setColor(QPalette::Highlight, lightHighlightColor);
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);
    lightPalette.setColor(QPalette::Link, lightLinkColor);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::ToolTipBase, lightHighlightColor);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Window, lightComplementColor);
    lightPalette.setColor(QPalette::WindowText, Qt::black);

    // Dark Mode shenanigans
    const QColor darkBaseColor(QStringLiteral("#32383D"));
    const QColor darkComplementColor(QStringLiteral("#202529"));
    const QColor darkDisabledColor(QStringLiteral("#4C555C"));
    const QColor darkHighlightColor(QStringLiteral("#A6AAAE"));
    const QColor darkLinkColor(QStringLiteral("#009BFF"));

    darkPalette = QPalette();
    darkPalette.setColor(QPalette::Active, QPalette::Button, darkDisabledColor.darker());
    darkPalette.setColor(QPalette::AlternateBase, darkComplementColor);
    darkPalette.setColor(QPalette::Base, darkBaseColor);
    darkPalette.setColor(QPalette::Button, darkComplementColor);
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, darkDisabledColor);
    darkPalette.setColor(QPalette::Disabled, QPalette::Light, darkComplementColor);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, darkDisabledColor);
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, darkDisabledColor);
    darkPalette.setColor(QPalette::Highlight, darkHighlightColor);
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    darkPalette.setColor(QPalette::Link, darkLinkColor);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::ToolTipBase, darkHighlightColor);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Window, darkComplementColor);
    darkPalette.setColor(QPalette::WindowText, Qt::white);

    QApplication::setPalette(lightPalette); // Set the light theme by default. Configs will toggle dark theme

    // Fill in the default data to prevent errors
    saveData.fill(QStringLiteral("0"), SAVELEN + 1);
    saveData.replace(0, QStringLiteral("null")); // Placeholder for unused data. Mostly for debugging
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
    auto *openFileAction = new QAction(QStringLiteral("Open file"));
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);

    auto *openIniAction = new QAction(QStringLiteral("Open ini"));
    connect(openIniAction, &QAction::triggered, this, &MainWindow::openIni);

    auto *saveAction = new QAction(QStringLiteral("Save"));
    saveAction->setEnabled(false);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);

    auto *saveAsAction = new QAction(QStringLiteral("Save As..."));
    saveAsAction->setEnabled(false);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::saveFileAs);

    auto *exitAction = new QAction(QStringLiteral("Exit"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Options actions
    auto *showDebugAction = new QAction(QStringLiteral("Show Debug"));
    showDebugAction->setCheckable(true);

    auto *showShrineAction = new QAction(QStringLiteral("Show Dog Shrine"));
    showShrineAction->setCheckable(true);

    auto *toggleDarkTheme = new QAction(QStringLiteral("Use Dark Theme"));
    toggleDarkTheme->setCheckable(true);

    auto *fetchDaily = new QAction(QStringLiteral("Check Daily"));
    fetchDaily->setCheckable(true);
    fetchDaily->setChecked(fetchDelay == FETCH_DAILY);

    auto *fetchWeekly = new QAction(QStringLiteral("Check Weekly"));
    fetchWeekly->setCheckable(true);
    fetchWeekly->setChecked(fetchDelay == FETCH_WEEKLY);

    auto *fetchMonthly = new QAction(QStringLiteral("Check Monthly"));
    fetchMonthly->setCheckable(true);
    fetchMonthly->setChecked(fetchDelay == FETCH_MONTHLY);

    connect(fetchDaily, &QAction::toggled, this, [fetchDaily, fetchWeekly, fetchMonthly, this]() -> void {
        // Block signals to prevent recursive activation
        const QSignalBlocker blockDaily(fetchDaily);
        const QSignalBlocker blockWeekly(fetchWeekly);
        const QSignalBlocker blockMonthly(fetchMonthly);

        fetchDaily->setChecked(true);
        fetchWeekly->setChecked(false);
        fetchMonthly->setChecked(false);

        fetchDelay = FETCH_DAILY;
    });
    connect(fetchWeekly, &QAction::toggled, this, [fetchDaily, fetchWeekly, fetchMonthly, this]() -> void {
        // Block signals to prevent recursive activation
        const QSignalBlocker blockDaily(fetchDaily);
        const QSignalBlocker blockWeekly(fetchWeekly);
        const QSignalBlocker blockMonthly(fetchMonthly);

        fetchDaily->setChecked(false);
        fetchWeekly->setChecked(true);
        fetchMonthly->setChecked(false);

        fetchDelay = FETCH_WEEKLY;
    });
    connect(fetchMonthly, &QAction::toggled, this, [fetchDaily, fetchWeekly, fetchMonthly, this]() -> void {
        // Block signals to prevent recursive activation
        const QSignalBlocker blockDaily(fetchDaily);
        const QSignalBlocker blockWeekly(fetchWeekly);
        const QSignalBlocker blockMonthly(fetchMonthly);

        fetchDaily->setChecked(false);
        fetchWeekly->setChecked(false);
        fetchMonthly->setChecked(true);

        fetchDelay = FETCH_MONTHLY;
    });

    // About menu actions
    auto *showAboutAction = new QAction(QStringLiteral("About"));
    connect(showAboutAction, &QAction::triggered, this, [this]() -> void {
        auto *about = new AboutDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        about->setAttribute(Qt::WA_DeleteOnClose, true); // This is important. It prevents multiple dialog windows from being stored in memory
        about->show();
    });

    // Tool actions
    auto *yellowNamesAction = new QAction(QStringLiteral("Set monster names yellow"));
    yellowNamesAction->setEnabled(false);
    connect(yellowNamesAction, &QAction::triggered, this, [this]() -> void {
        auto *yellowNamesDialog = new YellowNamesDialog(this, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
        yellowNamesDialog->setAttribute(Qt::WA_DeleteOnClose, true); // This is important. It prevents multiple dialog windows from being stored in memory
        yellowNamesDialog->show();

        emit toggleDarkMode(toggleOptions.option.darkMode);
    });

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
    icons->setUniformItemSizes(true);
    icons->setFlow(QListView::TopToBottom);
    icons->setWrapping(false);
    icons->setMovement(QListView::Static);
    icons->setItemAlignment(Qt::AlignCenter);
    icons->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    icons->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    // Give the main list fancy icons
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-player")), QStringLiteral("Player"), icons));
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-toriel")), QStringLiteral("Bosses"), icons));
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-froggit")), QStringLiteral("Monsters"), icons));
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-locations")), QStringLiteral("Locations"), icons));
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-debug")), QStringLiteral("Debug"), icons));
    buttons.append(new QListWidgetItem(QIcon(QStringLiteral(":/menu-shrine")), QStringLiteral("Dog Shrine"), icons));

    for (QListWidgetItem *item : buttons)
    {
        item->setSizeHint(QSize(84, 84)); // icon (64) + padding (20)
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
    const qint32 debugRow = icons->row(icons->findItems(QStringLiteral("Debug"), Qt::MatchFixedString).at(0));
    const qint32 shrineRow = icons->row(icons->findItems(QStringLiteral("Dog Shrine"), Qt::MatchFixedString).at(0));
    icons->setRowHidden(debugRow, !toggleOptions.option.showDebug);
    icons->setRowHidden(shrineRow, !toggleOptions.option.showShrine);
    icons->setFixedWidth(icons->sizeHintForColumn(0));

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

    // This section must happen after "icons" and "pages" are properly setup, otherwise the program crashes
    connect(icons, &QListWidget::currentRowChanged, this, [this](const int currentRow) -> void {
        pages->setCurrentIndex(currentRow);
    });
    icons->setCurrentRow(0);

    connect(showDebugAction, &QAction::toggled, this, [this](const bool checked) -> void {
        const qint32 debugRow = icons->row(icons->findItems(QStringLiteral("Debug"), Qt::MatchFixedString).at(0));
        icons->setRowHidden(debugRow, !checked);
        if (icons->isRowHidden(icons->currentRow()))
        {
            icons->setCurrentRow(0);
        }
        toggleOptions.option.showDebug = checked;
    });
    showDebugAction->setChecked(toggleOptions.option.showDebug);

    connect(showShrineAction, &QAction::toggled, this, [this](const bool checked) -> void {
        const qint32 shrineRow = icons->row(icons->findItems(QStringLiteral("Dog Shrine"), Qt::MatchFixedString).at(0));
        icons->setRowHidden(shrineRow, !checked);
        if (icons->isRowHidden(icons->currentRow()))
        {
            icons->setCurrentRow(0);
        }
        toggleOptions.option.showShrine = checked;
    });
    showShrineAction->setChecked(toggleOptions.option.showShrine);

    connect(toggleDarkTheme, &QAction::toggled, this, [this](const bool checked) -> void {
        QApplication::setPalette(checked ? darkPalette : lightPalette);
        toggleOptions.option.darkMode = checked;
        emit toggleDarkMode(checked);
    });
    const bool darkMode = toggleOptions.option.darkMode;
    toggleDarkTheme->setChecked(!darkMode); // Cycle the light/dark modes to apply them correctly
    toggleDarkTheme->setChecked(darkMode);

    connect(this, &MainWindow::enableControls, saveAction, &QAction::setEnabled);
    connect(this, &MainWindow::enableControls, saveAsAction, &QAction::setEnabled);
    connect(this, &MainWindow::enableTools, yellowNamesAction, &QAction::setEnabled);

    setCentralWidget(tabs);
#ifdef QT_DEBUG
    // Immediately open files to speedup testing
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
        const QJsonObject optionsJson = {
            { QStringLiteral("toggles"), static_cast<qint32>(toggleOptions.data) }
        };
        const QJsonObject updateJson = {
            { QStringLiteral("delay"), fetchDelay },
            { QStringLiteral("message"), fetchMessage },
            { QStringLiteral("time"), fetchTime },
            { QStringLiteral("version"), fetchVersion }
        };

        const QJsonObject json = {
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

    bool shouldFetchJson = false; // Assume we don't need to check for an update
    const QDateTime fetched = QDateTime::fromSecsSinceEpoch(fetchTime);
    const qint64 daysPassed = fetched.daysTo(QDateTime::currentDateTime());
    if (daysPassed > fetchDelay) // This is "close enough" to prevent the tool from checking during every start
    {
        shouldFetchJson = !isRemoteNewer(QApplication::applicationVersion(), fetchVersion); // If the "stored" version is newer, we can skip online check
        if (daysPassed > FETCH_BIANNUALLY) // Check anyway if six months have passed
        {
            shouldFetchJson = true;
        }

        if (!shouldFetchJson)
        {
            qDebug() << daysPassed << "day(s) has/have passed since the last prompt";
            QMetaObject::invokeMethod(this, &MainWindow::showVersionPrompt, Qt::QueuedConnection);
        }
    }

    if (shouldFetchJson)
    {
#ifdef QT_DEBUG
        // Test version fetching with a local version.json in "home path"
        const QUrl url(QStringLiteral("file://%1/version.json").arg(QDir::homePath()));
#else
        const QUrl url(QStringLiteral("https://raw.githubusercontent.com/Cofeiini/UndertaleSaveEditor/master/version.json"));
#endif
        auto *downloader = new FileDownloader(url, this); // Downloader will handle deleting itself, so a pointer is fine here
        connect(downloader, &FileDownloader::downloaded, this, &MainWindow::readDownloadedData);
    }
}

void MainWindow::fileModified(const bool modified)
{
    const QString obj = (sender() != nullptr) ? sender()->objectName() : objectName();
    const int opt = (static_cast<int>(modified) << 1) | static_cast<int>(changedEntries.contains(obj));
    switch (opt)
    {
        default: // case 0b00: // Not modified and not found. Usually this is a "reset"
        {
            break;
        }

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

    const auto value = static_cast<quint8>(!changedEntries.isEmpty());
    bitChange<quint8>(isModified, value, SAVED_FILE);
    tabs->setTabIcon(INDEX_FILE, floppy.at(value));
}

void MainWindow::iniModified(const bool modified)
{
    const QString obj = (sender() != nullptr) ? sender()->objectName() : objectName();
    const int opt = (static_cast<int>(modified) << 1) | static_cast<int>(changedIniEntries.contains(obj));
    switch (opt)
    {
        default: // case 0b00: // Not modified and not found. Usually this is a "reset"
        {
            break;
        }

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

    const auto value = static_cast<quint8>(!changedIniEntries.isEmpty());
    bitChange<quint8>(isModified, value, SAVED_INI);
    tabs->setTabIcon(INDEX_INI, floppy.at(value));
}

void MainWindow::openFile()
{
    if (!isSaved(SAVED_FILE))
    {
        return;
    }

    const CursorOverride cursorOverride;

#ifdef QT_DEBUG
    if (filePath.isEmpty())
    {
        filePath = QStringLiteral("%1/file0").arg(workDir);
    }
    else
#endif
    {
        const QString filter = QStringLiteral("Save file (file*);;All Files (*)");
        const QString path = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), workDir, filter);
        if (path.isEmpty())
        {
            return; // The user canceled the operation
        }
        filePath = path;
    }
    const QFileInfo info(filePath);
    workDir = info.dir().absolutePath();

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

    QTextStream input(&file);
    input.seek(0);
    for (int i = 1; i < SAVELEN; ++i)
    {
        saveData.replace(i, input.readLine().trimmed());
    }
    saveData.replace(SAVELEN, QString::number(static_cast<quint64>(input.readLine().trimmed().toDouble())));
    originalFile = saveData; // Make a copy for the "data changed" indicators
    fileErrors.clear();

    tabs->setTabEnabled(INDEX_FILE, true);
    tabs->setTabText(INDEX_FILE, info.fileName());
    tabs->setCurrentIndex(INDEX_FILE);

    changedEntries.clear();

    emit updateWidgets();
    emit enableControls(true);
    emit enableTools(true);

    if (!fileErrors.empty())
    {
        const auto position = fileErrors.at(0).indexOf(' ') + 1;
        std::sort(fileErrors.begin(), fileErrors.end(), [position](const QStringView &left, const QStringView &right) {
            return left.mid(position, 3).toFloat() < right.mid(position, 3).toFloat();
        });

        QMessageBox prompt(this);
        prompt.setWindowTitle(QApplication::applicationName());
        prompt.setText(QStringLiteral("There were some errors detected in %1 while parsing.\nCheck the details from more information.").arg(QDir::toNativeSeparators(filePath)));
        prompt.setDetailedText(QStringLiteral("%1").arg(fileErrors.join('\n')));
        prompt.setIcon(QMessageBox::Warning);
        prompt.exec();
    }
}

void MainWindow::openIni()
{
    if (!isSaved(SAVED_INI))
    {
        return;
    }

    const CursorOverride cursorOverride;

#ifdef QT_DEBUG
    if (iniPath.isEmpty())
    {
        iniPath = QStringLiteral("%1/undertale.ini").arg(workDir);
    }
    else
#endif
    {
        const QString filter = QStringLiteral("Ini File (*.ini);;All Files (*)");
        const QString path = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), workDir, filter);
        if (path.isEmpty())
        {
            return;
        }
        iniPath = path;
    }
    const QFileInfo info(iniPath);
    workDir = info.dir().absolutePath();

    const QSettings iniRead(iniPath, QSettings::IniFormat);
    for (const QString &item : iniRead.allKeys())
    {
        iniData.insert(item, iniRead.value(item));
    }
    originalIni = iniData;

    tabs->setTabEnabled(INDEX_INI, true);
    tabs->setTabText(INDEX_INI, info.fileName());
    tabs->setCurrentIndex(INDEX_INI);

    emit updateIniWidgets();
    emit enableControls(true);
}

void MainWindow::saveFile()
{
    if (tabs->currentIndex() == INDEX_FILE)
    {
        writeFile();
        return;
    }

    writeIni();
}

void MainWindow::saveFileAs()
{
    const int fileIndex = tabs->currentIndex();

    QString filter = QStringLiteral("Ini File (*.ini);;All Files (*)");
    if (fileIndex == INDEX_FILE)
    {
        filter = QStringLiteral("Save file (file*);;All Files (*)");
    }

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

    *(workPaths.value(fileIndex)) = path;

    saveFile();
}

void MainWindow::readDownloadedData(const QByteArray &data)
{
    const CursorOverride cursorOverride;

    const QJsonObject json = QJsonDocument::fromJson(data).object();
    fetchVersion = json["version"].toString();
    fetchMessage = json["message"].toString();
    fetchTime = QDateTime::currentSecsSinceEpoch(); // We need to set the time here to account for the online check

    if (isRemoteNewer(QApplication::applicationVersion(), fetchVersion))
    {
        qDebug() << "Found an update";
        QMetaObject::invokeMethod(this, &MainWindow::showVersionPrompt, Qt::QueuedConnection);
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

    if (prompt.exec() == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl(QStringLiteral("%1/releases").arg(GitHub_Url)));
    }
}

void MainWindow::showWriteError(const ErrorInfo &info)
{
    const QString text = QStringLiteral("Cannot write file %1").arg(QDir::toNativeSeparators(info.path));
    QMessageBox prompt(QMessageBox::Warning, QApplication::applicationName(), text, QMessageBox::Close, this);
    prompt.setDetailedText(info.message);
    prompt.exec();
}

auto MainWindow::isRemoteNewer(const QString &local, const QString &remote) -> bool
{
    QList<int> left;
    for (const QString &iter : local.split('.'))
    {
        bool isOk = true;
        int number = iter.toInt(&isOk);
        if (!isOk)
        {
            number = 0;
        }

        left.append(number);
    }
    left.resize(4); // Force the length to right size

    QList<int> right;
    for (const QString &iter : remote.split('.'))
    {
        bool isOk = true;
        int number = iter.toInt(&isOk);
        if (!isOk)
        {
            number = 0;
        }

        right.append(number);
    }
    right.resize(4); // Force the length to right size

    if (std::equal(left.begin(), left.end(), right.begin()))
    {
        return false; // This is a special case when the versions are the same
    }

    return std::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
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
    const CursorOverride cursorOverride;

    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        showWriteError({ filePath, file.errorString() });
        return;
    }

    file.resize(0);
    QTextStream out(&file);
    for (int i = 1; i < SAVELEN; ++i)
    {
        out << saveData.at(i) << '\n';
    }
    out << QString::number(saveData.at(SAVELEN).toDouble(), 'g', 5); // Handle time entry separately

    originalFile = saveData;
    changedEntries.clear();

    emit updateWidgets();
    fileModified(false);
}

void MainWindow::writeIni()
{
    const CursorOverride cursorOverride;

    const QString tempPath = QStringLiteral("%1.temp").arg(iniPath);
    QSettings iniOut(tempPath, QSettings::IniFormat);
    if (!iniOut.isWritable())
    {
        const QHash<QSettings::Status, QString> errorStrings {
            { QSettings::AccessError, QStringLiteral("Accessing the file failed") },
            { QSettings::FormatError, QStringLiteral("Reading the file format failed") },
        };

        showWriteError({ tempPath, errorStrings.value(iniOut.status(), QStringLiteral("Unknown error")) });
        return;
    }

    QFile file(iniPath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        showWriteError({ filePath, file.errorString() });
        return;
    }

    QHash<QString, QVariant> tempData(iniData); // Make a copy to freely edit the data

    // The data needs quotes around it to be a valid save format
    iniOut.setValue(QStringLiteral("Name"), QStringLiteral(R"("%1")").arg(tempData.value(QStringLiteral("Name")).toString())); // Handle the only exception in the data separately
    tempData.remove(QStringLiteral("Name")); // Remove the exception to make iterating simpler

    auto iter = tempData.constKeyValueBegin();
    const auto end = tempData.constKeyValueEnd();
    while (iter++ != end)
    {
        iniOut.setValue(iter->first, QStringLiteral(R"("%1")").arg(QString::number(iter->second.toDouble(), 'f', 6))); // Convert the data into the correct "double" format
    }
    iniOut.sync(); // Commit the changes to the file

    QFile tempFile(tempPath);
    if (!tempFile.open(QFile::ReadOnly | QFile::Text))
    {
        showWriteError({ tempPath, tempFile.errorString() });
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

    originalIni = iniData;
    changedIniEntries.clear();
    iniModified(false);
}
