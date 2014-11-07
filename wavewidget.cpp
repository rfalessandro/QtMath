#include "wavewidget.h"
#include "spectrumwidget.h"
#include <QPainter>
#include <math.h>
#include <soundutil.h>

WaveWidget::WaveWidget(QWidget *parent) :
    GraphWidget(parent)
{

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setMinimumSize(100,200);


}


void WaveWidget::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate)
{
    this->szSample = (int)(0.5 + (szBuffer / (nChannel * bitDepth)));
    int sec = (int)(0.5 + ((double)(szBuffer / (nChannel * bitDepth))  / (double)sampleRate ));
    zoom = ((double)width()/(double)(sampleRate*sec));
    createPoly(buffer, szBuffer, bitDepth, nChannel, true);

}


void WaveWidget::pushBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate)
{
    this->szSample += (int)(0.5 + (szBuffer / (nChannel * bitDepth)));
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


void WaveWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;

    xMax = 22050;
    deltaX = 1;
    deltaY = 1;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int middle = rect().height()/2;



    painter.setBrush(this->backgroundColor);

    painter.drawRect(0,0,width(),height());
    painter.drawLine(QPoint(0,middle), QPoint(width(),middle));

    painter.setPen(QPen(graphLineColor,1));



    if(lsPy != NULL) {
//        int maxY = 0;
//        for (int i = 0 ; i < lsPy->length() ; i++) {
//            int y = lsPy->at(i);
//            if(y > maxY) {
//                maxY = y;
//            }
//        }


        double c =  (double)height() / (double)yMax  ;
        double pos = 0;
        dx = std::min(dx, lsPy->length());

        painter.setBrush(this->graphBackgroundColor);
        double desloc = std::max(1.0 , 1.0/zoom);
        if(lsPy->length() > 0) {

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
                if(maxY < 0 ){
                    acc = -acc;
                }
                y = middle + maxY*c;
                acc = middle + acc*c;


                painter.setPen(this->graphBackgroundColor);
                painter.drawEllipse(pos-1, y-1, 2, 2);

                painter.drawLine(QPoint(pos, middle), QPoint(pos, y ));

                if(desloc>1) {
                    painter.setPen(this->graphLineColor);
                    painter.drawLine(QPoint(pos, middle), QPoint(pos, acc ));
                }


                pos++;
            }
        }
    }
    painter.end();
}
