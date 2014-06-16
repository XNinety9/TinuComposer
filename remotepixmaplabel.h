#ifndef REMOTE_PIXMAP_LABEL_H
#define REMOTE_PIXMAP_LABEL_H

#include <QLabel>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class RemotePixmapLabel: public QLabel
{
    Q_OBJECT
public:
    RemotePixmapLabel(QWidget* parent = 0) :
        QLabel(parent), networkManager(0)
    {}
    RemotePixmapLabel(const QString& text, QWidget* parent = 0) :
        QLabel(text, parent), networkManager(0)
    {
    }
public slots:
    void setRemotePixmap(const QString& /* url */);
private slots:
    void pixmapReceived(QNetworkReply*);
private:
    QNetworkAccessManager* networkManager;
};

#endif
