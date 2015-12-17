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
	void setter(const QString &target, const QVariant &value);

private slots:
	void boolSetter(bool value);
	void stringSetter(QString target, QString value);
	void accept();
	void reject();

public:
	explicit ConfigDialog(QWidget *parent = 0);

private:
	QString workPath;
	QHash<QString, QVariant> edict;
	QTabWidget *configTab;
	QDialogButtonBox *configBox;

};

class DefaultsTab : public QWidget
{
	Q_OBJECT

signals:
	QString getter(QString target) const;
	void stringSender(QString target, QString value);

private slots:
	void fileBrowse();
	void setter(const QString &target, const QVariant &value);

public:
	explicit DefaultsTab(QWidget *parent = 0);

private:
	QString workPath;
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
	void setter(const QString &target, const QVariant &value);

public:
	explicit FiltersTab(QWidget *parent = 0);

private:
	QVector<QWidget *> items;
};

#endif // CONFIGDIALOG_H
