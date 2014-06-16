#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QString>
#include <QImage>
#include <QList>
#include <QFileDialog>
#include <QStringList>
#include <QDir>

#include <xmlparser.h>

namespace Ui {
class MainDialog;
}


class MainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    QList<Software> list;
    QStringList cats;
    QString fileName;
    QDir tmpPath;
    int lastSelectedItem;

public slots:
    void openList();
    void newList();
    void newItem(Software s);
    void readFinished();
    void listItemChanged(int i);
    void retrieveIcon();
    void nameChanged(QString s);
    void versionChanged(QString s);
    void sizeChanged(QString s);
    void urlChanged(QString s);
    void appNameChanged(QString s);
    void addItem();
    void removeItem();
    void reload();
};

#endif // MAINDIALOG_H
