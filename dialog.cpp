#include "dialog.h"
#include "ui_dialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog) {
    ui->setupUi(this);

    connect(ui->cbImageFormat, &QComboBox::currentIndexChanged, this, &Dialog::updateFormatDescription);

    loadImageFormats();
}

Dialog::~Dialog() {
    delete ui;
}

void Dialog::loadImageFormats() {
    QFile f(":/resources/ImageFormats.json");
    f.open(QFile::ReadOnly);
    QString jsonStr = f.readAll();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonStr.toUtf8());

    for(int i = 1; i < jDoc.array().size(); i++) {
        QJsonObject jObj = jDoc.array().at(i).toObject();
        _formatDescriptions << jObj["Description"].toString();
        ui->cbImageFormat->addItem(jObj["Constant"].toString());
    }
    ui->cbImageFormat->setCurrentIndex(3);
    //TODO: Always use index + 1!!!
}

void Dialog::updateFormatDescription() {
    int index = ui->cbImageFormat->currentIndex();
    if(index != -1)
        ui->lImageFormatDescription->setText(_formatDescriptions[index]);
}
