#include "maindialog.h"
#include "ui_maindialog.h"

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog) {
    ui->setupUi(this);

    //disable UI for now
    ui->groupBoxList->setEnabled(false);
    ui->compile->setEnabled(false);

    //get temp QDir for later use
    tmpPath = QDir::temp();
}

MainDialog::~MainDialog() {
    delete ui;
}


void MainDialog::openList() {
    bool success = false;

    fileName = QFileDialog::getOpenFileName(this, tr("Open list file"), NULL, tr("List file (*.xml)"));

    if (fileName.isEmpty() == false) {
        XMLParser *xmlParser = new XMLParser(this);
        connect(xmlParser, SIGNAL(hasNewItem(Software)), this, SLOT(newItem(Software)));
        connect(xmlParser, SIGNAL(finished()), this, SLOT(readFinished()));

        success = xmlParser->readFile(fileName);
    }
}

void MainDialog::newList() {
    ui->groupBoxList->setEnabled(true);
    ui->compile->setEnabled(true);
}

void MainDialog::newItem(Software s) {
    list.append(s);
}

void MainDialog::readFinished() {
    //disconnect to avoid triggering listItemChanged when not needed.
    disconnect(ui->liste, SIGNAL(currentRowChanged(int)), this, SLOT(listItemChanged(int)));

    ui->liste->clear();
    foreach(Software s, list) {
        ui->liste->addItem(s.name);
        if (!cats.contains(s.cat))
            cats.append(s.cat);
    }

    ui->groupBoxList->setEnabled(true);
    ui->compile->setEnabled(true);

    connect(ui->liste, SIGNAL(currentRowChanged(int)), this, SLOT(listItemChanged(int)));
}

void MainDialog::listItemChanged(int i) {
    lastSelectedItem = i;

    //simple fields
    ui->name->setText(list.at(i).name);
    ui->size->setText(list.at(i).size);
    ui->version->setText(list.at(i).version);
    ui->url->setText(list.at(i).url);
    ui->app_name->setText(list.at(i).app_name);
    ui->desc->setPlainText(list.at(i).desc);

    //cats
    ui->cat->clear();
    ui->cat->addItems(cats);

    //icon
    QString listPath = fileName;
    listPath.chop(fileName.size()-(fileName.lastIndexOf("/")+1));
    ui->icon->setPixmap(QPixmap(listPath+list.at(i).icon));

    //actions
    if (list.at(i).actions.contains("unzip")) ui->unzip->setChecked(true);
    else ui->unzip->setChecked(false);
    if (list.at(i).actions.contains("untar")) ui->untar->setChecked(true);
    else ui->untar->setChecked(false);
    if (list.at(i).actions.contains("run")) ui->run->setChecked(true);
    else ui->run->setChecked(false);
    if (list.at(i).actions.contains("mount")) ui->mount->setChecked(true);
    else ui->mount->setChecked(false);
    if (list.at(i).actions.contains("move")) ui->move->setChecked(true);
    else ui->move->setChecked(false);
}

void MainDialog::retrieveIcon() {
    QString url = ui->iconurl->text();
    ui->icon->setRemotePixmap(url);
}

void MainDialog::nameChanged(QString s) {
    QListWidgetItem *qlwi = ui->liste->item(lastSelectedItem);
    qlwi->setText(s);
    list[lastSelectedItem].name = s;
}

void MainDialog::versionChanged(QString s) {
    list[lastSelectedItem].version = s;
}

void MainDialog::sizeChanged(QString s) {
    list[lastSelectedItem].size = s;
}

void MainDialog::urlChanged(QString s) {
    list[lastSelectedItem].url = s;
}

void MainDialog::appNameChanged(QString s) {
    list[lastSelectedItem].app_name = s;
}

void MainDialog::addItem() {
    Software s;

    s.name = "_New Entry";

    list.append(s);

    readFinished();
}

void MainDialog::reload() {

}

void MainDialog::removeItem() {

}

