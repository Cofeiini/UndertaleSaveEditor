#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QMap>
#include <QNetworkReply>
#include <QStackedWidget>

class FileDownloader : public QObject
{
	Q_OBJECT
public:
	FileDownloader(QUrl url, QObject *parent) : QObject(parent)
	{
		connect(&manager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(fileDownloaded(QNetworkReply*)));
		manager.get(QNetworkRequest(url));
	}
	QByteArray data;
signals:
	void downloaded();
private slots:
	void fileDownloaded(QNetworkReply* reply)
	{
		data = reply->readAll();
		reply->deleteLater();
		reply = nullptr;
		emit downloaded();
	}
private:
	QNetworkAccessManager manager;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent = nullptr);
	QStringList saveData = QString("null,Chara,1,20,20,10,0,10,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0").split(",");
	QMap<QString, QVariant> iniData;
protected:
	void closeEvent(QCloseEvent *event) override;
	void showEvent(QShowEvent * event) override;
signals:
	void updateWidgets();
	void updateIniWidgets();
public slots:
	void changePage(QListWidgetItem *current, QListWidgetItem *previous);
	void fileModified(bool value);
	void iniModified(bool value);
private slots:
	void openFile();
	void openIni();
	void saveFile();
	void saveFileAs();
	void loadData();
	void showDebug(bool checked);
	void showDog(bool checked);
private:
	bool checkIfFileSave();
	bool checkIfIniSave();
	void writeFile();
	void writeIni();

	FileDownloader *downloader;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *yellowNamesAction;
	QListWidget *icons;
	QStackedWidget *pages;
	QTabWidget *window;

	QString iniPath;
	QString filePath;
	QString workDir;
	QVector<QListWidgetItem *> buttons;
	QIcon floppy[2] = { QIcon(":/images/ico_floppy.png"), QIcon(":/images/ico_floppy_red.png") };

	bool isFileModified = false;
	bool isIniModified = false;
};

#endif // MAINWINDOW_H
