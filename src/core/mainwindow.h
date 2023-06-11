#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define TOGGLE_DARKMODE 1U
#define TOGGLE_SHOWDEBUG 2U
#define TOGGLE_SHOWSHRINE 4U

#include <QListWidget>
#include <QMainWindow>
#include <QStackedWidget>

#include "src/core/tools.h"

union Options {
	struct {
		bool darkMode : 1;
		bool showDebug : 1;
		bool showShrine : 1;
	} option;
	quint32 data;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT // NOLINT

public:
	explicit MainWindow(QWidget *parent = nullptr);

	static MainWindow *instance;
	static bool exists;
	static QMultiHash<int, CustomEditor *> editors;
	static QStringList saveData;
	static QStringList originalFile;
	static QStringList fileErrors;
	static QMultiHash<QString, CustomEditor *> iniEditors;
	static QHash<QString, QVariant> iniData;
	static QHash<QString, QVariant> originalIni;

public slots:
	void fileModified(const bool modified);
	void iniModified(const bool changed);

protected:
	void closeEvent(QCloseEvent *event) override;
	void showEvent(QShowEvent *event) override;

signals:
	void updateWidgets();
	void updateIniWidgets();
	void enableControls(const bool);
	void enableTools(const bool);
	void toggleDarkMode(const bool);

private slots:
	// File system stuff
	void openFile();
	void openIni();
	void saveFile();
	void saveFileAs();
	// Downloader stuff
	void readDownloadedData(const QByteArray &data);

private:
	void showVersionPrompt();
	void showWriteError(const QString &path, const QString &error);
	[[nodiscard("Value must be used.")]] auto isRemoteNewer(const QString &local, const QString &remote) -> bool;
	[[nodiscard("Value must be used.")]] auto isSaved(const quint8 modifiedBits) -> bool;
	void writeFile();
	void writeIni();

	QListWidget *icons = nullptr;
	QStackedWidget *pages = nullptr;
	QTabWidget *tabs = nullptr;

	QVector<QListWidgetItem *> buttons;
	QVector<QString> changedEntries;
	QVector<QString> changedIniEntries;

	QString iniPath;
	QString filePath;
	QString workDir;
	QString storeDir;
	quint8 isModified = 0;

	QString fetchVersion = QStringLiteral("0.0.0.0");
	QString fetchMessage = QStringLiteral("Improvements and bug fixes");
	qint64 fetchTime = 0;
    int fetchDelay = 30;
	Options toggleOptions = { { true, false, false } };

	QPalette lightPalette;
	QPalette darkPalette;

	const QVector<QIcon> floppy = { QIcon(QStringLiteral(":/saved")), QIcon(QStringLiteral(":/unsaved")) };
};

#endif // MAINWINDOW_H
