
#include "framepainter.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <algorithm>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <mathutil.h>
#include <stdio.h>
#include <QtGui>

FramePainter::FramePainter(QWidget *parent) :
    QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    backgroundColor = QColor( 0x22,0x33,0x55, 0xFF);
    graphLineColor = QColor(0x44, 0x88, 0x33, 0xFF);
    graphBackgroundColor = QColor(0x44, 0x88, 0x33, 0x88);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    pointColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    dx = 0;
    dy = 0;
    zoom = 0.01;
    pointDx = 0;
    elapsed = TIMEROUT;
    szBuffer = 0;    

}


void FramePainter::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate)
{
    this->nChannel = nChannel;
    this->bitDepth = bitDepth;
    this->szBuffer = szBuffer;
    this->buffer = buffer;
    this->sampleRate = sampleRate;

    createPoly();
}

void FramePainter::createPoly()
{
    if(graph == NULL) {
        delete (graph);
    }
    graph = new QPolygon;



    unsigned int i = 0,j = 0;
    graph->append(QPoint(0,0));
    for( i = 0; j < szBuffer ; i ++ ) {

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
        graph->append(QPoint(i, - value));
        j += (this->nChannel * this->bitDepth);
    }
    graph->append(QPoint(i,0));





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

    zoom = (zoom) + evt->delta()/120;
//    if(zoom < 0) {
//        zoom = (120 + zoom)/120;
//    }


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

double FramePainter::getZoom()
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

QColor FramePainter::getPointColor()
{
    return this->pointColor;
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

void FramePainter::setPointDx(int pointDx, bool isAnimation)
{
    if(this->pointDx != pointDx) {
        this->pointDx = pointDx;

        if(pointDx > dx + width()/zoom) {
            setDx(pointDx + (width()/zoom)/2 - 200/zoom) ;
            return;
        }

        //emit valueChanged();
        if(!isAnimation) {
            elapsed = TIMEROUT;
        }

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

void FramePainter::setZoom(double zoom)
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


void FramePainter::setPointColor(const QColor &pointColor)
{
    if(this->pointColor != pointColor) {
        this->pointColor = pointColor;
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


void FramePainter::animate()
{
    if(graph != NULL) {
        elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
        printf("{%d}\n", elapsed);
        setPointDx(std::min(((elapsed * this->sampleRate)/1000)  , graph->length()), true);
        //repaint();
    }
}


void FramePainter::drawBackground(QPainter *paint, QRect *rect)
{

    paint->fillRect(*rect, backgroundColor);
    paint->drawRect(*rect);
    int middle = rect->height()/2. + dy;

    paint->setPen(lineColor);
    paint->drawLine(0, middle, rect->width(), middle);


    double time = std::max(1., (this->sampleRate/5)*zoom);


    int aux1 = (middle - (1000 * zoom));
    int aux2 = (middle + (1000 * zoom));

    double dxZoom = dx * zoom;

    for(int i=0; i < rect->width() + dxZoom; i+= time ) {
        paint->drawLine(i - dxZoom , aux1, i -dxZoom , aux2);
    }

}


void FramePainter::drawGraph(QPainter *paint, QRect *rect)
{

    int middle = rect->height()/2. + dy;

    paint->setPen(graphLineColor);
    paint->setBrush(graphBackgroundColor);
    paint->setRenderHint(QPainter::Antialiasing);

    QMatrix translationTransform(1, 0, 0, 1, -dx*zoom, middle);
    QMatrix rotationTransform(1, 0, 0, 1, 0, 0);
    QMatrix scalingTransform(zoom, 0, 0, zoom, 0, 0);
    QMatrix transform = scalingTransform * rotationTransform * translationTransform;

    paint->setMatrix(transform);

    paint->drawPolygon(*graph);

    paint->setBrush(pointColor);
    if(graph != NULL && graph->size() > pointDx) {   
        printf("%d\n", pointDx);
        paint->drawEllipse( pointDx  - 50 , graph->at(pointDx).y()-50, 100,100);
    }
}


void FramePainter::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QRect *rect = new  QRect(this->rect().left(), this->rect().top(), this->rect().width() - 1, this->rect().height()-1);
    image = new QPixmap(rect->width(),rect->height());
    QPainter *paint = new QPainter(image);
    //QPainter *paint = new QPainter (this);


    paint->save();

    if(!paint->isActive()) {
        paint->begin (this);    
    }

    //paint->setClipRect(*rect);



    if(image == NULL) {
        delete (image);
    }



    drawBackground(paint, rect);
//  drawGraph(paint, rect);



    paint->drawPixmap(*rect, *image);



    paint->restore();

    paint->end ();




    delete paint;
    delete rect;
}


