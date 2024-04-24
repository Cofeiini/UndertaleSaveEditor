#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/core/tools.h"

#include <QListWidget>
#include <QMainWindow>
#include <QStackedWidget>

enum {
    INDEX_FILE = 0,
    INDEX_INI = 1,
};

union Options {
    struct {
        bool darkMode : 1;
        bool showDebug : 1;
        bool showShrine : 1;
    } option;

    quint32 data;
};

struct ErrorInfo {
    QString path;
    QString message;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

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

public slots: // NOLINT: False positive
    void fileModified(bool modified);
    void iniModified(bool modified);

protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent *event) override;

signals:
    void updateWidgets();
    void updateIniWidgets();
    void enableControls(bool);
    void enableTools(bool);
    void toggleDarkMode(bool);

private slots:
    // File system stuff
    void openFile();
    void openIni();
    void saveFile();
    void saveFileAs();
    // Downloader stuff
    void readDownloadedData(const QByteArray &data);

private: // NOLINT: False positive
    void showVersionPrompt();
    void showWriteError(const ErrorInfo &info);
    [[nodiscard]] static bool isRemoteNewer(const QString &local, const QString &remote);
    [[nodiscard]] bool isSaved(quint8 modifiedBits);
    void writeFile();
    void writeIni();

    QListWidget *icons = nullptr;
    QStackedWidget *pages = nullptr;
    QTabWidget *tabs = nullptr;

    QList<QListWidgetItem *> buttons;
    QList<QString> changedEntries;
    QList<QString> changedIniEntries;

    QString iniPath;
    QString filePath;
    QString workDir;
    QString storeDir;
    quint8 isModified = 0;

    QString fetchVersion = QStringLiteral("0.0.0.0");
    QString fetchMessage = QStringLiteral("Improvements and bug fixes");
    qint64 fetchTime = 0;
    qint32 fetchDelay = 30;
    Options toggleOptions = { { true, false, false } };

    QPalette lightPalette;
    QPalette darkPalette;

    const QList<QIcon> floppy { QIcon(QStringLiteral(":/saved")), QIcon(QStringLiteral(":/unsaved")) };
    QHash<qint32, QString *> workPaths { { INDEX_FILE, &filePath }, { INDEX_INI, &iniPath } };
};

#endif // MAINWINDOW_H
