#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent) {
    setWindowFlags(Qt::Window);
    resize(512, 512);
    setWindowTitle("MemoryArt - Canvas");
}

Canvas::~Canvas() {
}

void Canvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.drawImage(0, 0, _img);
}

void Canvas::setImage(const QImage &img) {
    _img = img.scaled(width(), height());
    update();
}
