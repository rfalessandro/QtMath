#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "audioscene.h"
#include <QApplication>
#include <math.h>
#include <sound.h>
#include <stdlib.h>
#include <stdio.h>
#include <QFuture>
#include <mathutil.h>
#include <QTimer>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tela = new AudioScene;

    ui->vlFrame->addWidget((QWidget *)this->tela);


    ui->btRecord->setDisabled(true);

    tela->setBackgroundColor(QColor(0xF0, 0xF7, 0xF2));
    tela->setLineColor(QColor(0xF4, 0xAC, 0x50, 0x70));
    tela->setPointColor(QColor(0x14, 0xe1, 0x2c, 0x99));    
    //tela->setGraphLineColor(QColor(0x67, 0x95, 0x94, 90));
    tela->setGraphLineColor(QColor(0x2D, 0x67, 0x69));
    tela->setGraphBackgroundColor(QColor(0xD5, 0xEB, 0xE7, 70));





    connect(ui->btRecalc, SIGNAL(released()), this, SLOT(recalc()));
    connect(tela, SIGNAL(valueChanged()), this, SLOT(updateMain()));
    connect(ui->btPlay, SIGNAL(released()), this, SLOT(playSound()));
    connect(ui->btRecord, SIGNAL(released()), this, SLOT(recordSound()));
    connect(ui->sbDx, SIGNAL(valueChanged(int)), this, SLOT(updateFrame()));
    connect(ui->sbDy, SIGNAL(valueChanged(int)), this, SLOT(updateFrame()));
    connect(ui->sbZoom, SIGNAL(valueChanged(double)), this, SLOT(updateFrame()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSin, SIGNAL(triggered()), this, SLOT(openMakeGraph()));
    connect(ui->cbDevice, SIGNAL(currentIndexChanged(int)), this, SLOT(changeDevice()));

    sound = new Sound;
    connect(this->sound, SIGNAL(startSound()), this, SLOT(soundStatus()));
    connect(this->sound, SIGNAL(stopSound()), this, SLOT(soundStatus()));
    connect(this->sound, SIGNAL(errorSignal(int, const QString &)), this, SLOT(soundError(int, const QString &)));
    connect(this->sound, SIGNAL(progress(unsigned int, double, const char *)), this, SLOT(soundProgess(unsigned int, double, const char *)));
    threadSound = new QThread;

    sound->moveToThread(threadSound);
    connect(threadSound, SIGNAL(started()), sound, SLOT(process()));
    threadSound->start();

    const std::vector<QString> *lsDev = sound->getPlaybackList();
    for (unsigned int i=0 ; i < lsDev->size() ; i++) {
        QString aux = lsDev->at(i);
        ui->cbDevice->addItem(aux.split(":").at(0), aux );
    }

    rawInfoDlg = new  RawInfoDialog(this);
    connect(rawInfoDlg, SIGNAL(accepted()), this, SLOT(acceptRawInfo()));

    graphDlg = new  DialogMakeGraph(this);
    connect(graphDlg, SIGNAL(accepted()), this, SLOT(makeGraph()));

    szBuffer = 0;
    buffer = NULL;


    ui->cbFormat->addItem(" 8 Bits ",  1);
    ui->cbFormat->addItem(" 16 Bits ", 2);
    ui->cbFormat->addItem(" 24 Bits ", 3);
    ui->cbFormat->addItem(" 32 Bits ", 4);
    ui->cbFormat->setCurrentIndex(1);






    updateMain();
}


MainWindow::~MainWindow()
{
    if(buffer != NULL) {
        free(buffer);
    }
    threadSound->exit();
    delete threadSound;
    delete sound;
    delete tela;
    delete ui;
}

void MainWindow::updateMain()
{
    ui->sbDx->setValue( tela->getDx() ) ;
    ui->sbDy->setValue( tela->getDy() );
    ui->sbZoom->setValue(tela->getZoom() );
}

void MainWindow::recalc() {
    tela->setDx(ui->sbDx->value());
    tela->setDy(ui->sbDy->value());
    tela->setZoom(ui->sbZoom->value());
    tela->repaint();

}

void MainWindow::updateFrame()
{
    tela->setDx(ui->sbDx->value());
    tela->setDy(ui->sbDy->value());
    tela->setZoom(ui->sbZoom->value());
}

void MainWindow::makeGraph()
{
    if(buffer != NULL) {
        free(buffer);
    }

    this->buffer = graphDlg->getGraph();
    this->bitDepth = graphDlg->getBitDepth();
    this->nChannel = graphDlg->getNChannel();
    this->sampleRate = graphDlg->getSampleRate();
    this->szBuffer = sampleRate * bitDepth * nChannel;


    updateSoundInfo();
}

void MainWindow::playSound()
{
    if(sound->isPlaying()) {
        sound->stop();
        tela->stopAnimate();
    }else {
        if(szBuffer > 0) {
            sound->setBuffer(buffer, szBuffer);
            sound->setSampleRate(sampleRate);
            sound->setBitDepth(this->bitDepth);
            sound->setNChannel(nChannel);
            sound->setTime(ui->sbSec->value() * 1000000);
            sound->setDeviceName(ui->cbDevice->currentData().toString().toStdString().c_str());
            threadSound->quit();

            tela->setDx(0);
            tela->setDy(0);
            tela->setPointPos(0,0);
            tela->animate(ui->sbSec->value() * 1000);


            threadSound->start();
        }else {
            QMessageBox messageBox;
            messageBox.information(this,"Info","No sound to play!");
            messageBox.setFixedSize(500,200);
        }
    }
}

void MainWindow::soundError(int errorType, const QString &errorStr)
{

    QMessageBox messageBox;
    messageBox.setFixedSize(500,200);
    switch (errorType) {
        case Sound::ERROR_OPEN_DEVICE:
        case Sound::ERROR_PARAMS_DEVICE:
            tela->stopAnimate();
            messageBox.critical(this,"Error", errorStr);
            break;
        default:
            messageBox.critical(this,"Error", "Error while playing");
            break;
    }



}
void MainWindow::soundStatus()
{    
    if(sound->isPlaying()) {
        ui->btPlay->setText("Stop");        
    }else {
        threadSound->exit();
        ui->btPlay->setText("Play");
    }    
}


void MainWindow::soundProgess(unsigned int value, double sec, const char *)
{
    ui->lbSecs->setText(  QString::number( sec , 'g', 3) + "s");
}

void MainWindow::openMakeGraph()
{
    graphDlg->setModal(true);
    graphDlg->open();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sound"), "", tr("All File (*.*)"));
    if(fileName != NULL && fileName.length() > 0) {
        QFile file(fileName);
        if(file.exists()) {
            rawInfoDlg->setModal(true);
            rawInfoDlg->setFileName(fileName);
            rawInfoDlg->open();
        }else {
            QMessageBox messageBox;
            messageBox.critical(this,"Error","File not found !");
            messageBox.setFixedSize(500,200);
        }
    }
}

void MainWindow::acceptRawInfo()
{

    QFile file(rawInfoDlg->getFileName());
    if (!file.open(QIODevice::ReadOnly))  {
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Cannot open the File!");
        messageBox.setFixedSize(500,200);
    }

    if(buffer != NULL) {
        free(buffer);
    }
    szBuffer = file.size();
    buffer = (unsigned char *) calloc ( sizeof(unsigned char) , szBuffer);
    file.read((char *)buffer, szBuffer);


    this->bitDepth = rawInfoDlg->getBitDepth();
    this->sampleRate = rawInfoDlg->getSampleRate();
    this->nChannel = rawInfoDlg->getNChannel();
    updateSoundInfo();





}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Sound"), "", tr("All File (*.*)"));
    if(fileName != NULL && fileName.length() > 0) {
          QFile file(fileName);
          if (!file.open(QIODevice::WriteOnly))  {
            return;
          }
          file.write((char *)   buffer, szBuffer);
          file.close();
    }
}



void MainWindow::updateSoundInfo()
{
    ui->sbNChannel->setValue(this->nChannel);
    ui->cbFormat->setCurrentIndex(ui->cbFormat->findData(this->bitDepth));

    ui->btRecord->setDisabled(true);

    tela->setBuffer(buffer, szBuffer, bitDepth, nChannel, sampleRate);
    tela->repaint();

}


void MainWindow::changeDevice()
{
    ui->btRecord->setDisabled(true);
    QString dev = ui->cbDevice->currentData().toString();
    const vector<QString> *lsCap = sound->getCaptureList();
    for(unsigned int i = 0 ; i < lsCap->size() ; i++) {
        if(lsCap->at(i) == dev) {
            ui->btRecord->setDisabled(false);
            break;
        }
    }
}


void MainWindow::recordSound()
{
    this->nChannel = ui->sbNChannel->value();
    this->bitDepth = ui->cbFormat->currentData().toInt();

    szBuffer = this->sampleRate * ui->sbSec->value() * this->nChannel * this->bitDepth;
    if(buffer == NULL) {
        free(buffer);
    }
    buffer = (unsigned char *)calloc(sizeof(unsigned char), szBuffer);
    sound->setBuffer(buffer, szBuffer);
    sound->setSampleRate(sampleRate);
    sound->setBitDepth(this->bitDepth);
    sound->setNChannel(nChannel);
    sound->setTime(ui->sbSec->value() * 1000000);
    sound->setDeviceName(ui->cbDevice->currentData().toString().toStdString().c_str());
    threadSound->quit();
    threadSound->start();
}
