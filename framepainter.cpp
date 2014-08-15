#include "framepainter.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <algorithm>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <mathutil.h>

FramePainter::FramePainter(QWidget *parent) :
    QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    backgroundColor = QColor( 0x22,0x33,0x55, 0xFF);
    graphLineColor = QColor(0x44, 0x88, 0x33, 0xFF);
    graphBackgroundColor = QColor(0x44, 0x88, 0x33, 0x88);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);

    dx = 0;
    dy = 0;
    zoom = 1;

    szBuffer = 0;

}


void FramePainter::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel)
{
    this->nChannel = nChannel;
    this->bitDepth = bitDepth;
    this->szBuffer = szBuffer;
    this->buffer = buffer;
}


void FramePainter::mousePressEvent(QMouseEvent *evt)
{
    this->ptOld = evt->globalPos();
}

void FramePainter::mouseMoveEvent(QMouseEvent *evt)
{
    const QPoint delta = evt->globalPos() - ptOld;
    dx = std::max(0, dx - ( delta.x()) );
    dy =  dy + ( delta.y()) ;
    ptOld = evt->globalPos();

    repaint();
    emit valueChanged();
}

void FramePainter::wheelEvent(QWheelEvent *evt)
{
    zoom = std::max(1, zoom + evt->delta()/120);

    //dx =  std::max(0, this->rect().width() -  (evt->globalX()  ) / zoom );
    //printf(" [%d] ", dx );
    //dy = evt->globalY();
    repaint();
    emit valueChanged();
}


int FramePainter::getDy()
{
    return this->dy;
}

int FramePainter::getDx()
{
    return this->dx;
}

int FramePainter::getZoom()
{
    return this->zoom;
}

QColor FramePainter::getBackgroundColor()
{
    return this->backgroundColor;
}

QColor FramePainter::getLineColor()
{
    return this->lineColor;
}

QColor FramePainter::getGraphBackgroundColor()
{
    return this->graphBackgroundColor;
}

QColor FramePainter::getGraphLineColor()
{
    return this->graphLineColor;
}

void FramePainter::setDy(int dy)
{
    if(this->dy != dy) {
        this->dy = dy;
        emit valueChanged();
        repaint();

    }

}

void FramePainter::setDx(int dx)
{
    if(this->dx != dx) {
        this->dx = dx;
        emit valueChanged();
        repaint();
    }
}

void FramePainter::setZoom(int zoom)
{
    if(this->zoom != zoom) {
        this->zoom = zoom;
        emit valueChanged();
        repaint();
    }
}

void FramePainter::setBackgroundColor(const QColor &backgroundColor)
{
    if(this->backgroundColor != backgroundColor) {
        this->backgroundColor = backgroundColor;
        repaint();
    }
}

void FramePainter::setLineColor(const QColor &lineColor)
{
    if(this->lineColor != lineColor) {
        this->lineColor = lineColor;
        repaint();
    }
}

void FramePainter::setGraphBackgroundColor(const QColor &graphBackgroundColor)
{
    if(this->graphBackgroundColor != graphBackgroundColor) {
        this->graphBackgroundColor = graphBackgroundColor;
        repaint();
    }
}

void FramePainter::setGraphLineColor(const QColor &graphLineColor)
{
    if(this->graphLineColor != graphLineColor) {
        this->graphLineColor = graphLineColor;
        repaint();
    }
}




void FramePainter::drawBackground(QPainter *paint, QRect *rect)
{

    paint->fillRect(*rect, backgroundColor);
    paint->drawRect(*rect);
    int middle = rect->height()/2. + dy;

    paint->setPen(lineColor);
    paint->drawLine(0, middle, rect->width(), middle);

    int aux1 = middle - 5  ;
    int aux2 = middle + 5 ;

    for(int i=0; i < rect->width() + dx; i+= 20 ) {
        paint->drawLine(i - dx , aux1, i -dx , aux2);
    }

}


void FramePainter::drawGraph(QPainter *paint, QRect *rect)
{

    int middle = rect->height()/2. + dy;
    QPolygon poly;
    poly << QPoint(0, middle);


    unsigned int j = dx * (this->nChannel * this->bitDepth) ;

    int i;
    for( i = 0; i < rect->width() + zoom  && j < szBuffer ; i += zoom ) {

        //int p = middle - pyList.at(j)  * zoom;
        int value = 0;
        switch ( this->bitDepth) {
            case 1:
                value = MathUtil::to8Le(buffer, j);
                break;
            case 2:
                value = MathUtil::to16Le(buffer, j);
                break;
            case 3:
                value = MathUtil::to24Le(buffer, j);
                break;
            case 4:
                value = MathUtil::to32Le(buffer, j);
                break;
            default:
                break;
        }
        value = value * zoom;
        int p = middle - value;
        paint->setBrush(graphLineColor);
        paint->drawEllipse(i-2, p-2, 4, 4 );
        poly << QPoint(i,p);
        j += (this->nChannel * this->bitDepth);
    }
    paint->setBrush(graphBackgroundColor);
    poly << QPoint( std::min(rect->width(), i) , middle);
    QPainterPath path;
    path.addPolygon(poly);
    paint->fillPath(path, graphBackgroundColor);
    paint->drawPolygon(poly);
}


void FramePainter::paintEvent(QPaintEvent *)
{
    QPainter *paint = new QPainter (this);
    QRect *rect = new  QRect(this->rect().left(), this->rect().top(), this->rect().width() - 1, this->rect().height()-1);

    if(!paint->isActive()) {
        paint->begin (this);
    }

    drawBackground(paint, rect);
    drawGraph(paint, rect);

    paint->end ();
    delete paint;
    delete rect;
}


