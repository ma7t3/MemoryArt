#include "dialog.h"
#include "ui_dialog.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    _canvas(new Canvas(this)),
    _timer(new QTimer(this)),
    _resolutionFloater(0),
    _resolutionFloatingDirection(true) {
    ui->setupUi(this);

    connect(_canvas, &Canvas::updateRequest, this, &Dialog::newImage);
    connect(_canvas, &Canvas::resolutionRequest, this, &Dialog::updateResolutionFromCanvas);

    connect(_timer, &QTimer::timeout, this, &Dialog::newImage);
    _timer->setSingleShot(false);

    connect(ui->twResolution, &QTabWidget::currentChanged, this, &Dialog::newImage);
    connect(ui->cbImageFormat, &QComboBox::currentIndexChanged, this, &Dialog::newImage);
    connect(ui->sbConstantSize, &QSpinBox::valueChanged, this, &Dialog::newImage);

    connect(ui->slFrequency, &QSlider::valueChanged, ui->sbFrequency, &QSpinBox::setValue);
    connect(ui->sbFrequency, &QSpinBox::valueChanged, ui->slFrequency, &QSlider::setValue);
    connect(ui->slFrequency, &QSlider::valueChanged, this, &Dialog::timerUpdate);

    QAction *showParentAction = addAction("");
    showParentAction->setShortcut(QKeySequence(Qt::Key_F1));
    connect(showParentAction, &QAction::triggered, this, [this](){
        if(!_canvas->isHidden())
            hide();
    });

    // actions
    QAction *startAction = addAction("");
    startAction->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Return));
    startAction->setShortcutContext(Qt::ApplicationShortcut);
    connect(startAction, &QAction::triggered, this, &Dialog::on_pbStart_clicked);

    loadImageFormats();
}

Dialog::~Dialog() {
    delete ui;
    delete _canvas;
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
}

void Dialog::updateFormatDescription() {
    int index = ui->cbImageFormat->currentIndex();
    if(index != -1)
        ui->lImageFormatDescription->setText(_formatDescriptions[index]);
}

void Dialog::on_pbStart_clicked() {
    _canvas->show();
}

void Dialog::updateResolutionFromCanvas(const bool &b) {
    if(ui->twResolution->currentIndex() != 0)
        return;

    int val = ui->sbConstantSize->value();
    ui->sbConstantSize->setValue(val + (b ? 1 : -1));
}

void Dialog::timerUpdate(const int &value) {
    if(value == 0)
        _timer->stop();
    else {
        float interval = (1.0 / (float)value) * 2000;
        _timer->setInterval(interval);
        _timer->start();
    }
}

void Dialog::newImage() {
    int size;
    if(ui->twResolution->currentIndex() == 0) {
        size = ui->sbConstantSize->value();
    } else {
        if(_resolutionFloater >= ui->sbMaxSize->value()) {
            _resolutionFloatingDirection = false;
        }
        if(_resolutionFloater <= ui->sbMinSize->value()) {
            _resolutionFloatingDirection = true;
        }
        size = _resolutionFloater;
    }

    QImage *img = new QImage(size, size, static_cast<QImage::Format>(ui->cbImageFormat->currentIndex() + 1));
    _canvas->setImage(*img);
    delete img;

    _resolutionFloater += (_resolutionFloatingDirection ? 1 : -1);
}

void Dialog::on_sbMinSize_valueChanged(int arg1) {
    if(arg1 > ui->sbMaxSize->value())
        ui->sbMaxSize->setValue(arg1);

    _resolutionFloater = std::min(std::max(_resolutionFloater, arg1), ui->sbMaxSize->value());
    newImage();
}

void Dialog::on_sbMaxSize_valueChanged(int arg1) {
    if(arg1 < ui->sbMinSize->value())
        ui->sbMinSize->setValue(arg1);

    _resolutionFloater = std::max(std::min(_resolutionFloater, arg1), ui->sbMinSize->value());
    newImage();
}
