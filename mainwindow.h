#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define TITLELABEL windowFilePath() + "[*]" + " - " + QApplication::applicationName() + " (v" + QApplication::applicationVersion() + ")"

#if defined(__linux__)
#  define UNDERTALE_PATH (QDir::homePath() + "/.config/UNDERTALE/")
#elif defined(__macosx__)
#  define UNDERTALE_PATH (QDir::homePath() + "/Library/Application Support/com.tobyfox.undertale/")
#else
#  define UNDERTALE_PATH (QDir::homePath() + "/AppData/Local/UNDERTALE/")
#endif

// I like having my includes in a single place
#include "configdialog.h"
#include "dataeditor.h"

#include <QCheckBox>
#include <QCloseEvent>
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QtMath>
#include <QMessageBox>
#include <QProgressBar>
#include <QSettings>
#include <QSpinBox>
#include <QTextBrowser>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	protected:
		void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
		void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

	private slots:
		bool on_actionFileSaveAs_triggered();
		bool on_actionFileSave_triggered();

		void configReciever();
		void dataBoolWasModified(int num);
		void dataComboWasModified(int num);
		void dataStringWasModified(QString string);
		void dataTimeWasModified(double num);
		void fileWasModified(bool mode);

		void on_actionConfigDialog_triggered();
		void on_actionFileExit_triggered();
		void on_actionFileNew_triggered();
		void on_actionFileOpen_triggered();
		void on_actionFileResetTransactionCancellation_triggered();
		void on_actionFileResetTrueReset_triggered();
		void on_actionFileResetUndo_triggered();


private:
		bool castWork();
		bool isModified;
		bool saveFile(const QDir &fileDir, const QString &fileName);
		int mResHeight;
		int mResWidth;
		int wMinHeight;
		int wMinWidth;
		void displayInfo();
		void loadFile(const QDir &fileDir, const QString &fileName);
		void readSettings();
		void setupEntries();
		void setupMenuBar();

		QDir workDir;
		QHash<int, QString> mem0, mem1, mem2, mem3, mem4;
		QHash<int, QString> tem0;
		QLabel *info[549];
		QLabel *numfo[549];
		QMap<QString, QString> law;
		QMap<QString, QVariant> edict;
		QStringList inilist;
		QStringList inivals;
		QStringList entryTypes;
		QString workFile;
		QTextBrowser *comment[549];
		QVector<int> stats;
		QVector<int> totalChanges;
		QVector<QWidget*> items;

		ConfigDialog *settingsDialog;
		Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
