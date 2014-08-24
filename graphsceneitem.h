#ifndef GRAPHSCENEITEM_H
#define GRAPHSCENEITEM_H

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>

class  GraphSceneItem : public QGraphicsItem
{
public:
    GraphSceneItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate);

protected:
    void advance(int phase);

private:
    qreal angle, speed;
    QPolygon *graph;
    unsigned const char *buffer;
    int sampleRate;
    int bitDepth;
    int nChannel;
    unsigned int szBuffer;

    void createPoly();
};

#endif // GRAPHSCENEITEM_h
