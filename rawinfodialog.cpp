#include "rawinfodialog.h"
#include "ui_rawinfodialog.h"

RawInfoDialog::RawInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RawInfoDialog)
{
    ui->setupUi(this);
    ui->txtSampleRate->setValidator( new QIntValidator(0, 999999999, this) );

    ui->cbFormat->addItem(" 8 Bits ",  1);
    ui->cbFormat->addItem(" 16 Bits ", 2);
    ui->cbFormat->addItem(" 24 Bits ", 3);
    ui->cbFormat->addItem(" 32 Bits ", 4);
    ui->cbFormat->setCurrentIndex(1);

    this->setWindowTitle("Raw Info");
}

RawInfoDialog::~RawInfoDialog()
{
    delete ui;
}


void RawInfoDialog::setFileName(QString name)
{
    this->fileName = name;
}

QString RawInfoDialog::getFileName()
{
    return this->fileName;
}


int RawInfoDialog::getBitDepth()
{
    return (ui->cbFormat->itemData(ui->cbFormat->currentIndex()).toInt());
}

int RawInfoDialog::getNChannel()
{
    return ui->sbNChannel->value();
}

int RawInfoDialog::getSampleRate()
{
    return  ui->txtSampleRate->text().toInt();
}

