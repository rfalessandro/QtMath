#include "audioitem.h"

#include <QPainter>

AudioItem::AudioItem()
{
    rect = new QRectF(0,0,10,10);
    backgroundColor = new QColor(0xFF, 0xFF, 0xFF, 0xFF);
    lineColor = new QColor(0xFF, 0xFF, 0xFF, 0xFF);
}

void AudioItem::setBoundinRect(QRectF *rect)
{
    this->rect = rect;
}

QRectF AudioItem::boundingRect() const
{
    return *rect;
}

void AudioItem::setBackgroundColor(const QColor *background)
{
    this->backgroundColor = background;
}

void AudioItem::setLineColor(const QColor *lineColor)
{
    this->lineColor = lineColor;
}


void AudioItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    painter->setPen(*this->lineColor);
    painter->setBrush(*backgroundColor);
    painter->drawLine(QPoint(0,0), QPoint(0,rect.height()));
    painter->drawEllipse(QPoint(0,rect.height()), rect.width(),rect.width());


}
