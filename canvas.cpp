#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent) :
    QDialog(nullptr),
    _parent(parent) {
    resize(512, 512);
    setWindowTitle("MemoryArt - Canvas");

    QAction *reloadAction = addAction("");
    reloadAction->setShortcut(QKeySequence(Qt::Key_Space));
    connect(reloadAction, &QAction::triggered, this, &Canvas::updateRequest);

    QAction *fullscreenAction = addAction("");
    fullscreenAction->setShortcut(QKeySequence(Qt::Key_F11));
    connect(fullscreenAction, &QAction::triggered, this, &Canvas::toggleFullscreen);

    QAction *showParentAction = addAction("");
    showParentAction->setShortcut(QKeySequence(Qt::Key_F1));
    connect(showParentAction, &QAction::triggered, this, &Canvas::toggleParent);

    QAction *increaseResolutionAction = addAction("");
    increaseResolutionAction->setShortcut(QKeySequence(Qt::Key_Up));
    connect(increaseResolutionAction, &QAction::triggered, this, [this](){emit resolutionRequest(true);});

    QAction *decreaseResolutionAction = addAction("");
    decreaseResolutionAction->setShortcut(QKeySequence(Qt::Key_Down));
    connect(decreaseResolutionAction, &QAction::triggered, this, [this](){emit resolutionRequest(false);});
}

Canvas::~Canvas() {
}

void Canvas::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);

    p.drawImage(0, 0, _img.scaled(width(), height()));
}

void Canvas::setImage(const QImage &img) {
    _img = img;
    update();
}

void Canvas::toggleFullscreen() {
    if(isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    };
}

void Canvas::toggleParent() {
    if(_parent->isHidden()) {
        _parent->show();
        _parent->activateWindow();
    } else {
        _parent->close();
    }
}
