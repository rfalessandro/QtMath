#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <math.h>
#include <sound.h>
#include <stdlib.h>
#include <stdio.h>
#include <QFuture>
#include <mathutil.h>
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tela = new FramePainter;
    ui->vlFrame->addWidget((QWidget *)this->tela);
    tela->setBackgroundColor(QColor(0xF0, 0xF7, 0xF2));
    tela->setLineColor(QColor(0x67, 0x95, 0x94, 0x70));
    tela->setPointColor(QColor(0x14, 0xe1, 0x2c, 0x99));
    tela->setGraphLineColor(QColor(0x67, 0x95, 0x94, 90));
    tela->setGraphBackgroundColor(QColor(0xD5, 0xEB, 0xE7, 70));



    ui->cbDepth->addItem(" 8 Bits ",  1);
    ui->cbDepth->addItem(" 16 Bits ", 2);
    ui->cbDepth->addItem(" 24 Bits ", 3);
    ui->cbDepth->addItem(" 32 Bits ", 4);

    ui->cbDepth->setCurrentIndex(1);

    connect(ui->cbDepth, SIGNAL(currentIndexChanged(int)), this, SLOT(makeGraph()));
    connect(ui->btRecalc, SIGNAL(released()), this, SLOT(recalc()));
    connect(tela, SIGNAL(valueChanged()), this, SLOT(updateMain()));
    connect(ui->btPlay, SIGNAL(released()), this, SLOT(playSound()));

    connect(ui->sbFreq, SIGNAL(valueChanged(int)), this, SLOT(makeGraph()));
    connect(ui->sbAmp, SIGNAL(valueChanged(int)), this, SLOT(makeGraph()));

    connect(ui->sbDx, SIGNAL(valueChanged(int)), this, SLOT(updateFrame()));
    connect(ui->sbDy, SIGNAL(valueChanged(int)), this, SLOT(updateFrame()));
    connect(ui->sbZoom, SIGNAL(valueChanged(double)), this, SLOT(updateFrame()));




    sound = new Sound;
    connect(this->sound, SIGNAL(startSound()), this, SLOT(soundStatus()));
    connect(this->sound, SIGNAL(stopSound()), this, SLOT(soundStatus()));
    connect(this->sound, SIGNAL(progress(unsigned int, double)), this, SLOT(soundProgess(unsigned int, double)));
    t = new QThread;

    sound->moveToThread(t);



    connect(t, SIGNAL(started()), sound, SLOT(process()));


    t->start();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), tela, SLOT(animate()));


    this->nChannel = 2;
//    this->bitDepth = 2;

    buffer = NULL;

    updateMain();
    makeGraph();


    new MathUtil();
}


MainWindow::~MainWindow()
{
    if(buffer != NULL) {
        free(buffer);
    }
    t->exit();
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


    this->bitDepth = (ui->cbDepth->itemData(ui->cbDepth->currentIndex()).toInt());



    int sampleRate = 44100;
    double w = ( 2 *  M_PI)/sampleRate;
    int frequency = ui->sbFreq->value();
    int amplitude = ui->sbAmp->value();




    szBuffer =  sampleRate * nChannel * this->bitDepth;

    if(buffer != NULL) {
        free(buffer);
    }
    buffer = (unsigned char *) calloc ( sizeof(unsigned char) , szBuffer);

    if(buffer == NULL || buffer == 0) {       
        return;
    }

    unsigned int j=0;
    unsigned char *aux = NULL;

    for(int i=0; i < sampleRate; i++ ) {

        int x =  round(sin(  i * w   * frequency ) * (amplitude));



        switch ( this->bitDepth) {
            case 1:
                aux = MathUtil::to8Le(x);
                break;
            case 2:
                aux = MathUtil::to16Le(x);
                break;
            case 3:
                aux = MathUtil::to24Le(x);
                break;
            case 4:                
                aux = MathUtil::to32Le(x);
                break;
            default:
                break;
        }

        for(int w=0; w < this->nChannel ; w++) {
            memcpy(buffer+j, aux, this->bitDepth);
            j += this->bitDepth;
        }
        if(aux != NULL)  {
            free(aux);
        }
    }


    tela->setBuffer(buffer, szBuffer, bitDepth, nChannel, sampleRate);

    tela->repaint();
}

void MainWindow::playSound()
{
    if(sound->isPlaying()) {
        sound->stop();
    }else {
        sound->setBuffer(buffer, szBuffer);
        sound->setSampleRate(sampleRate);
        sound->setBitDepth(this->bitDepth);
        sound->setNChannel(nChannel);
        sound->setTime(ui->sbSec->value() * 1000000);
        t->quit();
        t->start();
    }
}

void MainWindow::soundStatus()
{
    bool block;
    if(sound->isPlaying()) {
        ui->btPlay->setText("Stop");
        tela->setDx(0);
        tela->setDy(0);


        tela->setPointDx(0);
        timer->start(50);

        block = true;
    }else {
        t->exit();


        timer->stop();

        ui->btPlay->setText("Play");



        block = false;
    }
    ui->cbDepth->setDisabled(block);
    ui->sbAmp->setDisabled(block);
    ui->sbFreq->setDisabled(block);
    ui->sbSec->setDisabled(block);
}


void MainWindow::soundProgess(unsigned int value, double sec)
{    

//    tela->setPointDx(value);
    ui->lbSecs->setText(  QString::number( sec , 'g', 3) + "s");
}
