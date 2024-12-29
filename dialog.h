#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>

#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void loadImageFormats();
    void updateFormatDescription();
    void on_pbStart_clicked();

    void updateResolutionFromCanvas(const bool &);
    void timerUpdate(const int &);
    void newImage();

    void on_sbMinSize_valueChanged(int arg1);
    void on_sbMaxSize_valueChanged(int arg1);

private:
    Ui::Dialog *ui;

    QStringList _formatDescriptions;
    Canvas *_canvas;
    QTimer *_timer;

    int _resolutionFloater;
    bool _resolutionFloatingDirection;
};
#endif // DIALOG_H
