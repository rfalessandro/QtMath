#include "ball.h"
#include "audioscene.h"

#include <stdio.h>

Ball::Ball()
{    
    backgroundColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);

    // set the speed
    speed = 5;  // 5 pixels

    distance = 0;
    setPos(0,0);


}

QRectF Ball::boundingRect() const
{
    return QRect(-175,-175,350,350);
}

void Ball::setBackgroundColor(QColor background)
{
    this->backgroundColor = background;
}

void Ball::setLineColor(QColor lineColor)
{
    this->lineColor = lineColor;
}

void Ball::setSpeed(double value)
{
    this->speed = value;
}

void Ball::setMovement(qreal distance, double speed)
{
    this->speed = speed;
    this->distance = distance;
}


void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rect = boundingRect();

    painter->setPen(QPen(this->lineColor, 2));
    painter->setBrush(backgroundColor);
    painter->drawEllipse(rect);
}

void Ball::advance(int phase)
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


double Ball::getSpeed() const
{
    return this->speed;
}
