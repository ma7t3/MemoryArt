#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    void paintEvent(QPaintEvent *) override;

    void setImage(const QImage &);

private:
    QImage _img;
};

#endif // CANVAS_H
