#include "wavewidget.h"
#include "spectrumwidget.h"
#include <QPainter>
#include <math.h>
#include <QResizeEvent>
#include <stdio.h>
#include <soundutil.h>

WaveWidget::WaveWidget(QWidget *parent) :
    GraphWidget(parent)
{

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setMinimumSize(100,200);

}


void WaveWidget::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate, double time)
{

    zoomConst = ((double)width()/(double)(sampleRate*time));
    createPoly(buffer, szBuffer, bitDepth, nChannel, true);

}


void WaveWidget::pushBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate,  double time)
{
    zoomConst = ((double)width()/(double)(sampleRate*time));
    createPoly(buffer, szBuffer, bitDepth, nChannel, false);
}


void WaveWidget::createPoly(const unsigned char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, bool reset)
{
    if(reset) {
        clear();
    }
    unsigned int MAX_VALUE = ( 1 << (bitDepth*8 - 1 )) ;
    yMax = MAX_VALUE;
    unsigned int i,j,desloc;
    j=0;
    desloc=0;
    for( i = 0; j < szBuffer ; i ++ ) {
        int value = -SoundUtil::getIntValue(buffer, j, bitDepth);
        //graph->append(QPoint(desloc, value*cs));
        this->pushPy(value);
        j += (nChannel * bitDepth);
        desloc++;
    }
    repaint();
}

void WaveWidget::resizeEvent(QResizeEvent *e)
{
   this->QWidget::resizeEvent(e);
   zoomConst = (zoomConst *  (double)e->size().width()) / (double)e->oldSize().width();
}

void WaveWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int middle = rect().height()/2;

    painter.setBrush(this->backgroundColor);
    painter.drawRect(0,0,width(),height());
    painter.drawLine(QPoint(0,middle), QPoint(width(),middle));
    painter.setPen(QPen(graphLineColor,1));



    if(lsPy != NULL) {
        double c =  (double)height() / (double)yMax  ;
        double pos = 0;
        dx = std::min(dx, lsPy->length());

        painter.setBrush(this->graphBackgroundColor);
        double desloc = std::max(0.0 , 1.0/(zoom*zoom*zoomConst));
        if(lsPy->length() > 0) {
            if(desloc >= 1) {
                for (int i = dx ; i + desloc< lsPy->length() && pos < width() ; i += desloc) {


                    double maxY = 0, y = 0;
                    double acc = 0;
                    for(int j=0; j < desloc; j++) {
                        y = lsPy->at(i+j);
                        if(abs(y) > abs(maxY)) {
                            maxY = y;
                        }
                        acc += y*y;
                    }
                    acc = sqrt(acc/desloc);


                    maxY = maxY*c;//calc here for performace

                    y = middle + maxY;



                    painter.setPen(this->graphBackgroundColor);
                    painter.drawEllipse(pos-1, y-1, 2, 2);



                    if(desloc>5) {
                        acc = acc*c;//calc here for performace
                        double y2 = middle - maxY;
                        double acc2 = middle - acc;
                        acc = middle + acc;
                        painter.drawLine(QPoint(pos, y2), QPoint(pos, y ));
                        painter.setPen(this->graphLineColor);
                        painter.drawLine(QPoint(pos, acc2), QPoint(pos, acc ));
                    }else {
                       painter.drawLine(QPoint(pos, middle), QPoint(pos, y ));
                    }
                    pos++;
                }
            }else {
                desloc = 1/desloc;
                double lastY=0;
                double lastX=0;
                for (int i = dx ; i + desloc< lsPy->length() && pos < width() ; i ++) {
                    double maxY = 0, y = 0;

                    maxY = lsPy->at(i)*c;//calc here for performace

                    y = middle + maxY;
                    painter.setPen(this->graphBackgroundColor);
                    painter.drawEllipse(pos-1, y-1, 2, 2);                    
                    painter.drawLine(QPoint(pos, middle), QPoint(pos, y ));

                    painter.setPen(this->graphLineColor);
                    painter.drawLine(QPoint(lastX, lastY), QPoint(pos, y));

                    lastY = y;
                    lastX = pos;
                    pos+=desloc;

                }
            }
        }
    }
    painter.end();
}
