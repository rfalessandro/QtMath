#include "dialogmakegraph.h"
#include "ui_dialogmakegraph.h"
#include <math.h>
#include "mathutil.h"
DialogMakeGraph::DialogMakeGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMakeGraph)
{
    ui->setupUi(this);


    ui->cbDepth->addItem(" 8 Bits ",  1);
    ui->cbDepth->addItem(" 16 Bits ", 2);
    ui->cbDepth->addItem(" 24 Bits ", 3);
    ui->cbDepth->addItem(" 32 Bits ", 4);
    ui->cbDepth->setCurrentIndex(1);
}

DialogMakeGraph::~DialogMakeGraph()
{
    delete ui;
}




unsigned char  *DialogMakeGraph::getGraph()
{
    int bitDepth = (ui->cbDepth->itemData(ui->cbDepth->currentIndex()).toInt());
    int sampleRate = 44100;
    int nChannel = 2;
    double w = ( 2 *  M_PI)/sampleRate;
    int frequency = ui->sbFreq->value();
    int amplitude = ui->sbAmp->value();

    unsigned int szBuffer =  sampleRate * nChannel * bitDepth;

    unsigned char *buffer = (unsigned char *) calloc ( sizeof(unsigned char) , szBuffer);

    if(buffer == NULL || buffer == 0) {
        return NULL;
    }

    unsigned int j=0;
    unsigned char *aux = NULL;

    for(int i=0; i < sampleRate; i++ ) {

        int x =  round(sin(  i * w   * frequency ) * (amplitude));
        switch (bitDepth) {
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

        for(int w=0; w < nChannel ; w++) {
            memcpy(buffer+j, aux, bitDepth);
            j += bitDepth;
        }
        if(aux != NULL)  {
            free(aux);
        }
    }

   return buffer;


}


int DialogMakeGraph::getBitDepth()
{
    return (ui->cbDepth->itemData(ui->cbDepth->currentIndex()).toInt());
}

int DialogMakeGraph::getNChannel()
{
    return 2;
}

int DialogMakeGraph::getSampleRate()
{
    return 44100;
}

int DialogMakeGraph::getFrequency()
{
    return ui->sbFreq->value();
}

int DialogMakeGraph::getAmplitude()
{
    return ui->sbAmp->value();
}
