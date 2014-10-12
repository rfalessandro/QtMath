#include "spectrumwidget.h"
#include <QPainter>
#include <math.h>
#include <soundutil.h>

SpectrumWidget::SpectrumWidget(QWidget *parent) :
    GraphWidget(parent)
{
    binConst = 44100.0/65536.0;
}




void SpectrumWidget::updateGraph()
{

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
        int pos = 0;
        dx = std::min(dx, lsPy->length());
        painter.setPen(this->graphBackgroundColor);
        for (int i = dx ; i < lsPy->length() && pos < width() ; i++) {
            if(i!= 0 && i%400 == 0) {
                painter.setPen(QPen(fontColor,2));
                painter.drawText(pos - 20, 20,  QString::number(i) + "Hz");
                painter.setPen(this->lineColor);
                painter.drawLine(QPoint(pos, 0), QPoint(pos, height()));

                painter.setPen(this->graphBackgroundColor);
            }

            double y = middle - lsPy->at(i / binConst) * c;

            painter.setBrush(this->graphLineColor);
            painter.drawEllipse(pos-1, y-1, 2, 2);


            painter.drawLine(QPoint(pos,middle), QPoint(pos, y));
            pos+=1;
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
