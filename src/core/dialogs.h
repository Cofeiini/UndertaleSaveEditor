#ifndef DIALOGS_H
#define DIALOGS_H

#include <QCloseEvent>
#include <QDialog>
#include <QHash>

class AboutDialog : public QDialog
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit AboutDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private:
    static auto GetCredits() -> QString;
};

class YellowNamesDialog : public QDialog
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit YellowNamesDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

private:
    bool isQuit = true;
};

#endif // DIALOGS_H
