#include "audioscene.h"
#include <QtAlgorithms>
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
#include <audioitem.h>
AudioScene::AudioScene(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

    scene = new QGraphicsScene(this);

    ball = NULL;

    ball = new Ball();



    backgroundColor = QColor( 0x22,0x33,0x55, 0xFF);
    graphLineColor = QColor(0x44, 0x88, 0x33, 0xFF);
    graphBackgroundColor = QColor(0x44, 0x88, 0x33, 0x88);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);


    dx = 0;
    dy = 0;
    zoom = 0.2;
    pointDx = 0;
    szBuffer = 0;



    setScene(scene);

    //setSceneRect(QRect(0,0,this->width()-10,this->height()-10));
    //scene->setSceneRect(dx, dy, this->width()-10, this->height()-10);

    setRenderHint(QPainter::Antialiasing);




    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),scene, SLOT(advance()));
    connect(timer, SIGNAL(timeout()),this, SLOT(advance()));
    timer->start(TIMEROUT);




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
    if(scene->items().indexOf(ball) > -1) {
        scene->removeItem(ball);
    }

    scene->clear();;
    unsigned int i = 0,j = 0;

    AudioItem *item;

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
        //graph->append(QPoint(i, - value));

        AudioItem *item = new AudioItem;
        item->setPos(i,-value);
        item->setLineColor((QColor *)&graphLineColor);
        item->setBackgroundColor((QColor *)&graphBackgroundColor);
        scene->addItem(item);
        j += (this->nChannel * this->bitDepth);
    }
    ball->setMovement(0, 0 );
    ball->setBackgroundColor(pointColor);
    ball->setLineColor(graphLineColor);
    scene->addItem(ball);
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


int AudioScene::getDy() const
{
    return this->dy;
}

int AudioScene::getDx() const
{
    return this->dx;
}

double AudioScene::getZoom() const
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
        scene->setBackgroundBrush(backgroundColor);
    }
}

void AudioScene::setLineColor(const QColor &lineColor)
{
    if(this->lineColor != lineColor) {
        this->lineColor = lineColor;
    }
}


void AudioScene::setPointColor(const QColor &pointColor)
{
    if(this->pointColor != pointColor) {
        this->pointColor = pointColor;
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


void AudioScene::animate(unsigned int msec)
{
    if(ball != NULL) {
        double sz = (double)szBuffer/(this->bitDepth*this->nChannel);
        //funciona assim
        qreal speed =  ( sz / (msec / TIMEROUT)) * (this->bitDepth*this->nChannel) ;
        ball->setMovement( sz, speed  );
    }
}


void AudioScene::stopAnimate()
{
    if(ball != NULL) {
        ball->setSpeed(0);
        ball->setPos(0,0);
        setDx(0);
        setDy(0);
    }
}


void AudioScene::pauseAnimate()
{
    if(ball != NULL) {
        ball->setSpeed(0);
    }
}




void AudioScene::setPointPos(int x, int y) {
    ball->setPos(x, y);
}


void AudioScene::updateSceneRect()
{
    int middle = rect().height()/2. + dy;
    setTransform(QTransform().scale(zoom, zoom));
    scene->setSceneRect(dx, -middle, width(), height());


}




AudioScene::~AudioScene()
{

    delete timer;
    delete ball;
    delete scene;

}



void AudioScene::advance(int phase)
{
    if(!phase)
        return;
    if(ball != NULL) {
        if(ball->getSpeed() > 0) {
            if((ball->pos().x() ) > mapToScene(width(),0).x()) {
                setDx(ball->pos().x() + width());
            }
        }
    }

}
