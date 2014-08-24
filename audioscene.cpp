#include "audioscene.h"
#include "myitem.h"
#include <QPainter>
#include <QtCore/qmath.h>
#include <algorithm>
#include <QMouseEvent>
#include <QPoint>
#include <QApplication>
#include <mathutil.h>
#include <stdlib.h>
#include <QtGui>
#include <QGraphicsPolygonItem>

AudioScene::AudioScene(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    scene = new QGraphicsScene(this);

    graph =  NULL;
    buffer = NULL;

    backgroundColor = QColor( 0x22,0x33,0x55, 0xFF);
    graphLineColor = QColor(0x44, 0x88, 0x33, 0xFF);
    graphBackgroundColor = QColor(0x44, 0x88, 0x33, 0x88);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    pointColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    dx = 0;
    dy = 0;
    zoom = 1;
    pointDx = 0;
    elapsed = TIMEROUT;
    szBuffer = 0;




    setScene(scene);

    //setSceneRect(QRect(0,0,this->width()-10,this->height()-10));
    //scene->setSceneRect(dx, dy, this->width()-10, this->height()-10);

    setRenderHint(QPainter::Antialiasing);
    MyItem *item = new MyItem();
    scene->addItem(item);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),scene, SLOT(advance()));
    timer->start(100);



}





void AudioScene::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate)
{
    this->nChannel = nChannel;
    this->bitDepth = bitDepth;
    this->szBuffer = szBuffer;
    this->buffer = buffer;
    this->sampleRate = sampleRate;

    createPoly();
}

void AudioScene::createPoly()
{

    if(graph == NULL) {
        graph = new QPolygon;
    }else {
        scene->removeItem(graphPoly);
        delete graph;
    }
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



   graphPoly = new  QGraphicsPolygonItem(*graph);
   scene->addItem(graphPoly);


    updateSceneRect();
    repaint();
}

void AudioScene::mousePressEvent(QMouseEvent *evt)
{
    this->ptOld = evt->globalPos();
}

void AudioScene::mouseMoveEvent(QMouseEvent *evt)
{
    const QPoint delta = evt->globalPos() - ptOld;
    dx = std::max(0, dx - ( delta.x()) );
    dy =  dy + ( delta.y()) ;
    ptOld = evt->globalPos();

    updateSceneRect();
    emit valueChanged();
}

void AudioScene::wheelEvent(QWheelEvent *evt)
{

    zoom = (zoom) + evt->delta()/120;
//    if(zoom < 0) {
//        zoom = (120 + zoom)/120;
//    }


    //dx =  std::max(0, this->rect().width() -  (evt->globalX()  ) / zoom );
    //printf(" [%d] ", dx );
    //dy = evt->globalY();
    updateSceneRect();
    emit valueChanged();
}


int AudioScene::getDy()
{
    return this->dy;
}

int AudioScene::getDx()
{
    return this->dx;
}

double AudioScene::getZoom()
{
    return this->zoom;
}

QColor AudioScene::getBackgroundColor()
{
    return this->backgroundColor;
}

QColor AudioScene::getLineColor()
{
    return this->lineColor;
}

QColor AudioScene::getPointColor()
{
    return this->pointColor;
}

QColor AudioScene::getGraphBackgroundColor()
{
    return this->graphBackgroundColor;
}

QColor AudioScene::getGraphLineColor()
{
    return this->graphLineColor;
}

void AudioScene::setDy(int dy)
{
    if(this->dy != dy) {
        this->dy = dy;
        emit valueChanged();
        updateSceneRect();
    }
}

void AudioScene::setPointDx(int pointDx, bool isAnimation)
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

        updateSceneRect();
    }
}

void AudioScene::setDx(int dx)
{
    if(this->dx != dx) {
        this->dx = dx;
        emit valueChanged();
        updateSceneRect();
    }
}

void AudioScene::setZoom(double zoom)
{
    if(this->zoom != zoom) {
        this->zoom = zoom;
        emit valueChanged();
        updateSceneRect();
    }
}

void AudioScene::setBackgroundColor(const QColor &backgroundColor)
{
    if(this->backgroundColor != backgroundColor) {
        this->backgroundColor = backgroundColor;
        updateSceneRect();
    }
}

void AudioScene::setLineColor(const QColor &lineColor)
{
    if(this->lineColor != lineColor) {
        this->lineColor = lineColor;
        updateSceneRect();
    }
}


void AudioScene::setPointColor(const QColor &pointColor)
{
    if(this->pointColor != pointColor) {
        this->pointColor = pointColor;
        updateSceneRect();
    }
}

void AudioScene::setGraphBackgroundColor(const QColor &graphBackgroundColor)
{
    if(this->graphBackgroundColor != graphBackgroundColor) {
        this->graphBackgroundColor = graphBackgroundColor;
        updateSceneRect();
    }
}

void AudioScene::setGraphLineColor(const QColor &graphLineColor)
{
    if(this->graphLineColor != graphLineColor) {
        this->graphLineColor = graphLineColor;
        updateSceneRect();
    }
}


void AudioScene::animate()
{
//    if(graph != NULL) {
//        elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval());
//        printf("{%d}\n", elapsed);
//        setPointDx(std::min(((elapsed * this->sampleRate)/1000)  , graph->length()), true);
//        //updateSceneRect();
//    }

}





void AudioScene::updateSceneRect()
{
    int middle = rect().height()/2. + dy;
    QMatrix translationTransform(1, 0, 0, 1, -dx*zoom, middle);
    QMatrix rotationTransform(1, 0, 0, 1, 0, 0);
    QMatrix scalingTransform(zoom, 0, 0, zoom, 0, 0);
    QMatrix transform = scalingTransform * rotationTransform * translationTransform;
    QList<QGraphicsItem *> ls = scene->items();
    for (int i =0 ;i< ls.length() ;i++) {
        ls.at(i)->setMatrix(transform);
    }

}
