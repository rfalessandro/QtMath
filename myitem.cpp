#include "myitem.h"
#include "audioscene.h"
MyItem::MyItem()
{

    // set the speed
    speed = 15;  // 5 pixels

    // random start position
    int startX = 0;
    int startY = 0;

    setPos(mapToParent(startX, startY));
}

QRectF MyItem::boundingRect() const
{
    return QRect(0,0,20,20);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();


    QPen pen(Qt::red, 2);
    painter->setPen(pen);
    painter->drawEllipse(rect);
}

void MyItem::advance(int phase)
{
    if(!phase) return;

//    const AudioScene *t = (AudioScene *)scene();
//    if(t != NULL) {
//        int d = t->getDx();
//        setPos(mapToParent(d, -speed));
//    }
}


