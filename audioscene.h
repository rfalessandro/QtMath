#ifndef AUDIOSCENE_H
#define AUDIOSCENE_H
#include "ball.h"
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
    Ball *ball;
    unsigned const char *buffer;
    QGraphicsPolygonItem *graphPoly;
    QColor backgroundColor;
    QColor lineColor;
    QColor pointColor;
    QColor graphBackgroundColor;
    QColor graphLineColor;
    QPoint ptOld;
    int dy;
    int dx;
    int pointDx;
    double zoom;
    int sampleRate;
    int bitDepth;
    int nChannel;
    unsigned int szBuffer;
    void createPoly();

public:
    explicit AudioScene(QWidget *parent = 0);
    ~AudioScene();

    static const int TIMEROUT = 50;

    int getDy() const;
    int getDx() const;
    double getZoom() const;
    QColor getBackgroundColor();
    QColor getLineColor();
    QColor getPointColor();
    QColor getGraphBackgroundColor();
    QColor getGraphLineColor();

    void setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate);
    void setPointPos(int x, int y);
    void setDy(int dy);
    void setDx(int dx);    
    void setZoom(double zoom);
    void setBackgroundColor(const QColor &backgroundColor);
    void setLineColor(const QColor &lineColor);
    void setPointColor(const QColor &graphLineColor);
    void setGraphBackgroundColor(const QColor &graphBackgroundColor);
    void setGraphLineColor(const QColor &graphLineColor);
    void updateSceneRect();
    void animate(unsigned int msec);
    void pauseAnimate();
    void stopAnimate();
signals:
    void valueChanged();
public slots:

protected slots:
    void advance(int phase = 1);


};






#endif // AUDIOSCENE_H
