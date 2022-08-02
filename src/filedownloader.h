#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class FileDownloader : public QObject
{
	Q_OBJECT

public:
	explicit FileDownloader(const QUrl url, QObject *parent = nullptr) : QObject{parent}
	{
		connect(&manager, &QNetworkAccessManager::finished, this, [=] (QNetworkReply *reply) -> void {
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
