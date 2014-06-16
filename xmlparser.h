#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QString>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <QImage>


struct Software {
    QString name;
    QString version;
    QString size;
    QString url;
    QString app_name;
    QString actions;
    QString cat;
    QString icon;
    QString desc;
    QImage icon_image;
};


class XMLParser : public QObject {
    Q_OBJECT

public:
    XMLParser(QObject *parent = 0);
    bool readFile(const QString &fileName);

private:
    QList<Software> *_liste;

signals:
    void finished();
    void hasNewItem(Software s);
};

#endif // XMLPARSER_H
