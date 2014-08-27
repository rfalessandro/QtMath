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
    if(!phase) {
        return;
    }
    QPointF newP = mapToParent( +speed , 0  );
    if(newP.x() <= distance) {
        setPos( newP);
    }else {
        speed = 0;
    }


//    if(newP.x() > mapToParent(scene()->sceneRect().x(), 0).x()) {

//    }
}


double MyItem::getSpeed() const
{
    return this->speed;
}
