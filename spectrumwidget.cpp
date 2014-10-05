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
        int max = 0;
        for (int i = 0 ; i < lsPy->length() ; i++) {
            int y = lsPy->at(i);
            if(y > max) {
                max = y;
                }
            }
        double c =  (double)height() / (double)max  ;
        int pos = 0;
        dx = std::min(dx, lsPy->length());

        for (int i = dx ; i < lsPy->length() && pos < width() ; i++) {
            if(i!= 0 && i%400 == 0) {
                painter.setPen(QPen(fontColor,2));
                painter.drawText(pos, 20,  QString::number(i) + "Hz");
                painter.setPen(QPen(graphLineColor,1));
            }
            max = lsPy->at(i) *c;
            painter.setBrush(this->graphBackgroundColor);
            painter.drawLine(QPoint(pos,middle), QPoint(pos, middle - max));
            pos++;
        }
    }
    painter.end();
}
