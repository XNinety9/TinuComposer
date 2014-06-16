#include "RemotePixmapLabel.h"

#include <QPixmap>
#include <QUrl>
#include <QDebug>

void RemotePixmapLabel::setRemotePixmap(const QString& url) {
    if (!networkManager) {
        networkManager = new QNetworkAccessManager(this);
        connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(pixmapReceived(QNetworkReply*)));
    }

    networkManager->get(QNetworkRequest(QUrl(url)));
}

void RemotePixmapLabel::pixmapReceived(QNetworkReply* reply) {
    if (QNetworkReply::NoError != reply->error()) {
        clear();
        setText("No icon :'(");
        reply->deleteLater();
        return;
    }

    const QByteArray data(reply->readAll());

    QPixmap pixmap;
    pixmap.loadFromData(data);
    setPixmap(pixmap);

    reply->deleteLater();
}
