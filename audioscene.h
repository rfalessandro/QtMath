#ifndef AUDIOSCENE_H
#define AUDIOSCENE_H
#include "myitem.h"
#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
class AudioScene : public QGraphicsView
{
    Q_OBJECT

protected:

    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void wheelEvent(QWheelEvent *evt);
private:
    QGraphicsScene *scene;

    QTimer *timer;
    unsigned const char *buffer;
    QColor backgroundColor;
    QColor lineColor;
    QColor graphBackgroundColor;
    QColor graphLineColor;

    MyItem *ball;
    QPolygon *graph;
    QGraphicsPolygonItem *graphPoly;




    int dy;
    int dx;
    int pointDx;
    double zoom;


    int sampleRate;
    int bitDepth;
    int nChannel;
    unsigned int szBuffer;


    void createPoly();

    QPoint ptOld;

    int elapsed;
public:
    explicit AudioScene(QWidget *parent = 0);


    static const int TIMEROUT = 50;

    int getDy();
    int getDx();
    int getPointDx();


    double getZoom();
    QColor getBackgroundColor();
    QColor getLineColor();
    QColor getPointColor();
    QColor getGraphBackgroundColor();
    QColor getGraphLineColor();

    void setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate);

    void setDy(int dy);
    void setDx(int dx);
    void setPointDx(int dx, bool isAnimation=false );
    void setZoom(double zoom);
    void setBackgroundColor(const QColor &backgroundColor);
    void setLineColor(const QColor &lineColor);
    void setPointColor(const QColor &graphLineColor);
    void setGraphBackgroundColor(const QColor &graphBackgroundColor);
    void setGraphLineColor(const QColor &graphLineColor);
    void updateSceneRect();
    void animate(unsigned int msec);
signals:
    void valueChanged();
public slots:



};






#endif // AUDIOSCENE_H
