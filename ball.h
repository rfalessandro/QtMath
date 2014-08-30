#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class Ball : public QGraphicsItem
{
public:
    Ball();
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
    qreal distance;
    double speed;
    QColor lineColor;
    QColor backgroundColor;
};

#endif // BALL_H
