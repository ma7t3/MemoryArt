#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

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

    void loadImageFormats();

public slots:
    void updateFormatDescription();

private:
    Ui::Dialog *ui;

    QStringList _formatDescriptions;
};
#endif // DIALOG_H
