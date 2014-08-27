#ifndef MYITEM_H
#define MYITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class MyItem : public QGraphicsItem
{
public:
    MyItem(QGraphicsView *view);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setLineColor(QColor lineColor);
    void setBackgroundColor(QColor background);
    void setSpeed(double value);
    void setMovement(qreal distance, double speed);
    double getSpeed() const;
protected:
    void advance(int phase);

private:
    QGraphicsView *view;
    qreal distance;
    double speed;
    QColor lineColor;
    QColor backgroundColor;
};

#endif // MYITEM_H
