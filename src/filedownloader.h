#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class FileDownloader : public QObject
{
    Q_OBJECT // NOLINT: Framework code, so can't fix this

public:
    explicit FileDownloader(const QUrl &url, QObject *parent = nullptr) :
        QObject { parent }
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);

        connect(&manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply *reply) -> void {
            QApplication::restoreOverrideCursor();

            emit downloaded(reply->readAll());
            reply->deleteLater();
            deleteLater();
        });
        manager.get(QNetworkRequest(url));
    }

signals:
    void downloaded(const QByteArray &data);

private:
    QNetworkAccessManager manager;
};

#endif // FILEDOWNLOADER_H
