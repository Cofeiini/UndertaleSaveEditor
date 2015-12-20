#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QMap>
#include <QSettings>
#include <QTableWidget>
#include <QtWidgets>

class ConfigDialog : public QDialog
{
	Q_OBJECT

protected:
	void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;

signals:
	void configTransmitter();
	void initiator();
	void transmitter(const QString &target, const QVariant &value);

private slots:
	void accept();
	void boolReciever(const bool &value);
	void intReciever(const int &value);
	void reject();
	void stringReciever(const QString &target, const QString &value);

public:
	explicit ConfigDialog(QWidget *parent = 0);

private:
	QDialogButtonBox *configBox;
	QMap<QString, QVariant> edict;
	QString workPath;
	QTabWidget *configTab;
	void initSettings();

};

class DefaultsTab : public QWidget
{
	Q_OBJECT

signals:
	void stringTransmitter(const QString &target, const QString &value);

private slots:
	void fileBrowse();
	void initializer();
	void reciever(const QString &target, const QVariant &value);

public:
	explicit DefaultsTab(QWidget *parent = 0);

private:
	QDir workDir;
	QFile workFile;
	QLabel *autoDirLabel;
	QLabel *autoFileLabel;
	QVector<QWidget *> items;
};

class FiltersTab : public QWidget
{
	Q_OBJECT

private slots:
	void reciever(const QString &target, const QVariant &value);

public:
	explicit FiltersTab(QWidget *parent = 0);

private:
	QVector<QWidget *> items;
};

#endif // CONFIGDIALOG_H
