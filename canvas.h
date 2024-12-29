#ifndef CANVAS_H
#define CANVAS_H

#include <QDialog>

class Canvas : public QDialog
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void paintEvent(QPaintEvent *) override;
    void setImage(const QImage &);

private slots:
    void toggleFullscreen();
    void toggleParent();

signals:
    void updateRequest();
    void resolutionRequest(const bool &);

private:
    QImage _img;
    QWidget *_parent;
};

#endif // CANVAS_H
