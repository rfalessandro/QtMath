#ifndef FRAMEPAINTER_H
#define FRAMEPAINTER_H

#include <QWidget>


class FramePainter : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void wheelEvent(QWheelEvent *evt);
private:
    unsigned const char *buffer;
    QColor backgroundColor;
    QColor lineColor;
    QColor pointColor;
    QColor graphBackgroundColor;
    QColor graphLineColor;
    QPolygon *graph;

    int dy;
    int dx;
    int pointDx;
    double zoom;


    int sampleRate;
    int bitDepth;
    int nChannel;
    unsigned int szBuffer;


    void drawGraph(QPainter *paint, QRect *rect);
    void drawBackground(QPainter *paint, QRect *rect);
    void createPoly();

    QPoint ptOld;
public:
    explicit FramePainter(QWidget *parent = 0);    

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
    void setPointDx(int dx);
    void setZoom(double zoom);
    void setBackgroundColor(const QColor &backgroundColor);
    void setLineColor(const QColor &lineColor);
    void setPointColor(const QColor &graphLineColor);
    void setGraphBackgroundColor(const QColor &graphBackgroundColor);
    void setGraphLineColor(const QColor &graphLineColor);


signals:
    void valueChanged();
public slots:


};

#endif // FRAMEPAINTER_H
