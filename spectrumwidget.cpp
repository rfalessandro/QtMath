#include "spectrumwidget.h"
#include <QPainter>
#include <math.h>
#include <soundutil.h>

SpectrumWidget::SpectrumWidget(QWidget *parent) :
    GraphWidget(parent)
{
    binConst = 44100.0/65536.0;
}


void SpectrumWidget::setBuffer(const cplx *buffer, unsigned int szBuffer, unsigned int sampleRate)
{
    clear();
    this->binConst =     (double)sampleRate / (double)szBuffer;

    unsigned int nyquist = szBuffer/2;
    for (unsigned int i = 0; i < nyquist + 1  && i < szBuffer; i++) {
            cplx complexAux = (buffer[i] / szBuffer);

            if(i != 0 && i != nyquist) {
               complexAux  = (complexAux * 2);
            }

            double d1 = creal(complexAux) ;
            double d2 = cimag(complexAux) ;

            int d3 = (int)( sqrt(pow(d1,2) + pow(d2,2)) );
            this->pushPy(d3);

            //printf("%d hz: [%g  ; %g] = %g\n ", i, d1, d2, d3);
    }

    updateGraph();
}

void SpectrumWidget::updateGraph()
{
    this->repaint();
}

void SpectrumWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;

    xMax = 22050;
    yMax = 100;
    deltaX = 1;
    deltaY = 1;

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int middle = rect().height();



    painter.setBrush(this->backgroundColor);

    painter.drawRect(0,0,width(),height());
    painter.drawLine(QPoint(0,middle), QPoint(width(),middle));

    painter.setPen(QPen(graphLineColor,1));



    if(lsPy != NULL) {
        int maxY = 0;
        for (int i = 0 ; i < lsPy->length() ; i++) {
            int y = lsPy->at(i);
            if(y > maxY) {
                maxY = y;
            }
        }
        double c =  (double)height() / (double)maxY  ;
        double pos = 0;
        dx = std::min(dx, lsPy->length());

        painter.setPen(this->graphBackgroundColor);

        if(lsPy->length() > 0) {
            zoom  =   ((double)width()/((double)lsPy->length() )) /  binConst  ;;
            for (int i = dx ; i < lsPy->length() && pos < width() ; i++) {
                int binPos =  i / binConst;
                if(binPos >= lsPy->length()) {
                    break;
                }
                if(i == 800 || i == 2000 || i == 4000 || i == 9000 || i == 14000 || i == 18000 || i == 22000    ) {
                    painter.setPen(QPen(fontColor,2));
                    painter.drawText(pos - 20, 20,  QString::number(i).replace("000","K") + "Hz");
                    painter.setPen(QPen(this->lineColor, 1));
                    painter.drawLine(QPoint(pos, 0), QPoint(pos, height()));

                    painter.setPen(this->graphBackgroundColor);
                }

               // double y = middle - 20.0 * log( (lsPy->at(i / binConst) +1) ) ;
                double y = middle -   (lsPy->at(binPos)) * c ;

                painter.setBrush(this->graphLineColor);
                painter.drawEllipse(pos-1, y-1, 2, 2);


                painter.drawLine(QPoint(pos, middle), QPoint(pos, y ));
                pos+=zoom;
            }
        }
    }
    painter.end();
}


void SpectrumWidget::setBinConst(double value)
{
    this->binConst = value;
}
double SpectrumWidget::getBinConst() const
{
    return this->binConst;
}
