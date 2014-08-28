#ifndef RAWINFODIALOG_H
#define RAWINFODIALOG_H

#include <QDialog>
#include <QFile>

namespace Ui {
class RawInfoDialog;
}

class RawInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RawInfoDialog(QWidget *parent = 0);
    ~RawInfoDialog();
    void setFileName(QString name);
    QString getFileName();
    int getSampleRate();
    int getBitDepth();
    int getNChannel();


private:
    Ui::RawInfoDialog *ui;
    QString fileName;
};

#endif // RAWINFODIALOG_H
