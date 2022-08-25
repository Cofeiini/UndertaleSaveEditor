#ifndef INITOOLS_H
#define INITOOLS_H

#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

class MainWindow;

class CustomIniEditor : public QFrame
{
	Q_OBJECT // NOLINT

public:
	template<typename T>
	explicit CustomIniEditor(const QString &identifier, T **editorWidget, QWidget *buddyWidget = nullptr);

	void addHintText(const QString &text);
	std::function<void()> callback = [] () { /* Keep this empty. Otherwise we crash */ };

	QVBoxLayout *vLayout = new QVBoxLayout();
	QWidget *editor = nullptr;
	QLabel *label = nullptr;

	QString id;
	static const QHash<QString, int> editorIds;

signals:
	void dataChanged(const bool changed);

public slots:
	void updateSave(const bool hasChanged);
	virtual void updateData() { qDebug() << "Non-overloaded \"updateData\" was called!"; }

private:
	QWidget *buddy = nullptr;
};

class IniCheckBox : public CustomIniEditor
{
	Q_OBJECT // NOLINT

public:
	IniCheckBox(const QString &id, const QString &text, QWidget *buddyWidget = nullptr);

	QCheckBox *editor;

public slots:
	void updateSave(const int data);
	void updateData() override;

private:
	const std::vector<int> values = { 0, 1, 1 };
	const QHash<int, Qt::CheckState> states = { { 0, Qt::Unchecked }, { 1, Qt::Checked } };
};

class IniLineEdit : public CustomIniEditor
{
	Q_OBJECT // NOLINT

public:
	IniLineEdit(const QString &id, QWidget *buddyWidget = nullptr);

	QLineEdit *editor;

public slots:
	void updateSave(const QString &data);
	void updateData() override;
};

class IniSpinBox : public CustomIniEditor
{
	Q_OBJECT // NOLINT

public:
	IniSpinBox(const QString &id, QWidget *buddyWidget = nullptr);

	QDoubleSpinBox *editor;

public slots:
	void updateSave(const double data);
	void updateData() override;
};

#endif // INITOOLS_H
