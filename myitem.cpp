#include "myitem.h"
#include "audioscene.h"
MyItem::MyItem()
{
    backgroundColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);

    // set the speed
    speed = 5;  // 5 pixels

    // random start position
    int startX = 0;
    int startY = 0;

    setPos(0,0);
}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,50,50);
}

void MyItem::setBackgroundColor(QColor background)
{
    this->backgroundColor = background;
}

void MyItem::setLineColor(QColor lineColor)
{
    this->lineColor = lineColor;
}

void MyItem::setSpeed(qreal value)
{
    this->speed = value;
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

    const AudioScene *t = (AudioScene *)scene();
    if(t != NULL) {
        setPos(pos().x()+speed, pos().y());
    }
}


