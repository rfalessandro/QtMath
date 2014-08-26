#include "myitem.h"
#include "audioscene.h"

#include <stdio.h>

MyItem::MyItem(QGraphicsView *view)
{
    this->view = view;
    backgroundColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);

    // set the speed
    speed = 5;  // 5 pixels

    distance = 0;
    setPos(0,0);


}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,450,450);
}

void MyItem::setBackgroundColor(QColor background)
{
    this->backgroundColor = background;
}

void MyItem::setLineColor(QColor lineColor)
{
    this->lineColor = lineColor;
}

void MyItem::setSpeed(double value)
{
    this->speed = value;
}

void MyItem::setMovement(qreal distance, double speed)
{
    this->speed = speed;
    this->distance = distance;
}


void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();


    ;
    painter->setPen(QPen(this->lineColor, 2));
    painter->setBrush(backgroundColor);
    painter->drawEllipse(rect);
}

void MyItem::advance(int phase)
{
    if(!phase) return;


    AudioScene *t = (AudioScene *)view;
    if(t != NULL ) {
        qreal newX =  (pos().x()+speed);
        if(newX <= distance) {
            setPos( newX , pos().y()  );           
        }
//        int paiDx = t->getDx() + (t->width());
//        if(paiDx < newX ) {
//            t->setDx(newX + t->width()/2);
//        }

    }
}


