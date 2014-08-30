#ifndef AUDIOITEM_H
#define AUDIOITEM_H

#include <QGraphicsItem>
#include <QRectF>

class AudioItem : public QGraphicsItem
{    
private:
    const QColor *lineColor;
    const QColor *backgroundColor;
    QRectF *rect;
public:
    AudioItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setLineColor(const QColor *lineColor);
    void setBoundinRect(QRectF *rect);
    void setBackgroundColor(const QColor *background);
};

#endif // AUDIOITEM_H
