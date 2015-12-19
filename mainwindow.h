#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//For future releases. Right now I'm calling this a "preview".
#define TITLELABEL windowFilePath() + "[*]" + " - " + QApplication::applicationName() + " (v" + QApplication::applicationVersion() + ")"

// I like having my includes in a single place
#include "configdialog.h"

#include <QCheckBox>
#include <QCloseEvent>
//#include <QComboBox>
#include <QDebug>
#include <QDesktopWidget>
#include <QDir>
//#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QtMath>
#include <QMessageBox>
//#include <QPalette>
//#include <QPlainTextEdit>
#include <QProgressBar>
#include <QSettings>
#include <QSpinBox>
//#include <QString>
//#include <QStringListModel>
#include <QTextBrowser>
//#include <QTextStream>
//#include <QVariant>
//#include <QVector>
//#include <QWhatsThis>

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
		void configReciever();
		void dataBoolWasModified(int number);
		void dataSliderWasModified(int number);
		void dataStringWasModified(QString string);
		void dataTimeWasModified(double number);
		void fileWasModified(bool mode);

		bool on_actionFileSave_triggered();
		bool on_actionFileSaveAs_triggered();
		void on_actionFileExit_triggered();
		void on_actionFileNew_triggered();
		void on_actionFileOpen_triggered();
		void on_actionFileResetTransactionCancellation_triggered();
		void on_actionFileResetTrueReset_triggered();
		void on_actionFileResetUndo_triggered();

		void on_actionConfigDialog_triggered();

private:
		bool buildingInProgress;
		bool castWork();
		bool isModified;
		bool saveFile(const QDir &fileDir, const QString &fileName);
		bool unitReady;
		int mResHeight;
		int mResWidth;
		void displayInfo();
		void loadFile(const QDir &fileDir, const QString &fileName);
		void readSettings();
		void setupEntries();
		void setupMenuBar();
		void writeSettings();

		QAction *actionRefresh;
		QDir edictDir;
		QDir workDir;
		QHash<int, QString> mem0;
		QHash<int, QString> mem1;
		QHash<int, QString> mem2;
		QHash<int, QString> mem3;
		QHash<int, QString> mem4;
		QLabel *info[549];
		QLabel *numfo[549];
		QMap<QString, QVariant> edict;
		QMap<QString, QString> law;
		QString edictFile;
		QString workFile;
		QStringList inilist;
		QStringList inivals;
		QTextBrowser *comment[549];
		QVector<int> stats;
		QVector<QHBoxLayout*> itemRows;
		QVector<QWidget*> items;

		Ui::MainWindow *ui;
		ConfigDialog *settingsDialog;
};

#endif // MAINWINDOW_H
