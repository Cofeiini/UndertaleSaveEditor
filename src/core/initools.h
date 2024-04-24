#ifndef INITOOLS_H
#define INITOOLS_H

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

class MainWindow;

struct iniData {
    static const QHash<QString, int> idMap;
};

class CustomIniEditor : public QFrame
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    template<typename T>
    explicit CustomIniEditor(QString identifier, T *editorWidget, QWidget *buddyWidget = nullptr);

    void addHintText(const QString &text);
    std::function<void()> callback = []() { /* Keep this empty. Otherwise we crash */ };

    QVBoxLayout *vLayout = new QVBoxLayout();
    QWidget *editor = nullptr;
    QLabel *label = nullptr;

    QString id;

signals:
    void dataChanged(bool changed);

public slots:
    void updateSave(bool hasChanged);

    virtual void updateData()
    {
        qDebug() << R"(Non-overloaded "updateData" was called!)";
    }

private:
    QWidget *buddy = nullptr;
};

class IniCheckBox : public CustomIniEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    IniCheckBox(const QString &editorId, const QString &text, QWidget *buddyWidget = nullptr);

    QCheckBox *editor;

public slots: // NOLINT: False positive
    void updateSave(int data);
    void updateData() override;

private:
    std::vector<int> values = { 0, 1, 1 };
    QHash<int, Qt::CheckState> states = { { 0, Qt::Unchecked }, { 1, Qt::Checked } };
};

class IniLineEdit : public CustomIniEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit IniLineEdit(const QString &editorId, QWidget *buddyWidget = nullptr);

    QLineEdit *editor;

public slots: // NOLINT: False positive
    void updateSave(const QString &data);
    void updateData() override;
};

class IniSpinBox : public CustomIniEditor
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit IniSpinBox(const QString &editorId, QWidget *buddyWidget = nullptr);

    QDoubleSpinBox *editor;

public slots: // NOLINT: False positive
    void updateSave(double data);
    void updateData() override;
};

#endif // INITOOLS_H
