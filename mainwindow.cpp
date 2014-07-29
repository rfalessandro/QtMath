#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <math.h>
#include <sound.h>
#include <stdlib.h>
#include <QFuture>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tela = new FramePainter;
    ui->vlFrame->addWidget((QWidget *)this->tela);





    ui->cbDepth->addItem(" 8 Bits ",  1);
    ui->cbDepth->addItem(" 16 Bits ", 2);
   // ui->cbDepth->addItem(" 24 Bits ", 3);
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
    connect(ui->sbZoom, SIGNAL(valueChanged(int)), this, SLOT(updateFrame()));




    sound = new Sound;


    this->nChannel = 2;
//    this->bitDepth = 2;

    buffer = NULL;

    updateMain();
    makeGraph();
}


MainWindow::~MainWindow()
{
    if(buffer != NULL) {
        free(buffer);
    }
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
    buffer = (char*) malloc ( sizeof(char) *  szBuffer);
    memset(buffer, 0, szBuffer);

    if(buffer == NULL || buffer == 0) {
       //errorr
        return;
    }

    long j=0;
    u_int8_t a,b,c,d;
    tela->clearPy();
    for(int i=0; i < sampleRate; i++ ) {

        const u_int32_t x = (u_int32_t) round( sin(  i * w   * frequency ) * amplitude );

        tela->pushPy(x);     

        switch ( this->bitDepth) {
            case 1:
                buffer[j++] = (char)d;
                buffer[j++] = (char)d;
                break;
            case 2:
                b = (u_int8_t) ( (x >> 8 ) &  0x000000FF);//pega os 8 bits do lado
                a = (u_int8_t) ( (x >> 0 ) &  0x000000FF);//pega os 8bits do fim
                //left channel
                buffer[j++] = (char)a;
                buffer[j++] = (char)b;
                //right channel
                buffer[j++] = (char)a;
                buffer[j++] = (char)b;
                break;
            case 4:                
                d = (u_int8_t) ( (x >> 24  )  & 0x000000FF );//pega os 8 bits do lado fim
                c = (u_int8_t) ( (x >> 16  )  & 0x000000FF );//pega os 8 bits do meio
                b = (u_int8_t) ( (x >> 8   )  & 0x000000FF );//pega os 8 bits do lado
                a = (u_int8_t) ( (x >> 0   )  & 0x000000FF );//pega os 8bits do fim
                //left channell
                buffer[j++] = (char)a;
                buffer[j++] = (char)b;
                buffer[j++] = (char)c;
                buffer[j++] = (char)d;
                //right channel
                buffer[j++] = (char)a;
                buffer[j++] = (char)b;
                buffer[j++] = (char)c;
                buffer[j++] = (char)d;
                break;
            default:
                break;
        }
    }

    tela->repaint();

}

void MainWindow::playSound()
{
    sound->setBuffer(buffer, szBuffer);
    sound->setSampleRate(sampleRate);
    sound->setBitDepth(this->bitDepth);
    sound->setNChannel(nChannel);
    sound->setTime(ui->sbSec->value() * 1000000);
    //QFuture<void> thread = run(sound->play());
    //QFuture<void> thread;
    //thread.setPaused();
    //thread.waitForFinished();
    sound->play();
}
