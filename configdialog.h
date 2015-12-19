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
	void initiator();
	void transmitter(const QString &target, const QVariant &value);
	void configTransmitter();

private slots:
	void boolReciever(const bool &value);
	void intReciever(const int &value);
	void stringReciever(const QString &target, const QString &value);
	void accept();
	void reject();

public:
	explicit ConfigDialog(QWidget *parent = 0);

private:
	void initSettings();
	QString workPath;
	QMap<QString, QVariant> edict;
	QTabWidget *configTab;
	QDialogButtonBox *configBox;

};

class DefaultsTab : public QWidget
{
	Q_OBJECT

signals:
	void stringTransmitter(const QString &target, const QString &value);

private slots:
	void fileBrowse();
	void reciever(const QString &target, const QVariant &value);
	void initializer();

public:
	explicit DefaultsTab(QWidget *parent = 0);

private:
	QFile workFile;
	QDir workDir;
	QVector<QWidget *> items;
	QLabel *autoFileLabel;
	QLabel *autoDirLabel;
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
