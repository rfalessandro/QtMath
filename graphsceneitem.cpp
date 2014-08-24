#include "graphsceneitem.h"
#include "audioscene.h"
#include "mathutil.h"
GraphSceneItem::GraphSceneItem()
{
    graph = NULL;
    // set the speed
    speed = 15;  // 5 pixels

    // random start position
    int startX = 0;
    int startY = 0;

    setPos(mapToParent(startX, startY));
}

QRectF GraphSceneItem::boundingRect() const
{
    return QRect(0,0,20,20);
}

void GraphSceneItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(graph != NULL) {
        painter->drawPolygon(*graph);
    }
}

void GraphSceneItem::advance(int phase)
{
    if(!phase) return;

//    const AudioScene *t = (AudioScene *)scene();
//    if(t != NULL) {
//        int d = t->getDx();
//        setPos(mapToParent(d, -speed));
//    }
}




void GraphSceneItem::setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate)
{
    this->nChannel = nChannel;
    this->bitDepth = bitDepth;
    this->szBuffer = szBuffer;
    this->buffer = buffer;
    this->sampleRate = sampleRate;

    createPoly();
}

void GraphSceneItem::createPoly()
{
    if(graph == NULL) {
        graph = new QPolygon;
    }else {
        graph->clear();
    }
    unsigned int i = 0,j = 0;
    graph->append(QPoint(0,0));
    for( i = 0; j < szBuffer ; i ++ ) {

        //int p = middle - pyList.at(j)  * zoom;
        int value = 0;
        switch ( this->bitDepth) {
            case 1:
                value = MathUtil::to8Le(buffer, j);
                break;
            case 2:
                value = MathUtil::to16Le(buffer, j);
                break;
            case 3:
                value = MathUtil::to24Le(buffer, j);
                break;
            case 4:
                value = MathUtil::to32Le(buffer, j);
                break;
            default:
                break;
        }
        graph->append(QPoint(i, - value));
        j += (this->nChannel * this->bitDepth);
    }

    graph->append(QPoint(i,0));
}


