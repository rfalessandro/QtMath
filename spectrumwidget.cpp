#include "spectrumwidget.h"
#include <QPainter>

SpectrumWidget::SpectrumWidget(QWidget *parent) :
    GraphWidget(parent)
{
}




void SpectrumWidget::updateGraph()
{

}

void SpectrumWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;


    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int middle = rect().height()/2. + dy;


    painter.setBrush(this->backgroundColor);
    painter.setPen(QPen(lineColor,2));
    painter.drawRect(0,0,width(),height());
    painter.drawLine(QPoint(0,middle), QPoint(width(),middle));

    painter.setPen(QPen(graphLineColor,4));

    if(lsPy != NULL) {
        for (int i = 0 ; i < lsPy->length() ; i++) {
            painter.drawLine(QPoint(i,middle), QPoint(i, middle - lsPy->at(i)));
        }
    }



    painter.end();
}
