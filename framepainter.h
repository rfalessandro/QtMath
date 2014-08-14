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
    QColor graphBackgroundColor;
    QColor graphLineColor;
    int dy;
    int dx;
    int zoom;

    int bitDepth;
    int nChannel;
    int szBuffer;


    void drawGraph(QPainter *paint, QRect *rect);
    void drawBackground(QPainter *paint, QRect *rect);


    QPoint ptOld;
public:
    explicit FramePainter(QWidget *parent = 0);    

    int getDy();
    int getDx();
    int getZoom();
    QColor getBackgroundColor();
    QColor getLineColor();
    QColor getGraphBackgroundColor();
    QColor getGraphLineColor();

    void setBuffer(unsigned const char *buffer, int szBuffer, int bitDepth, int nChannel);

    void setDy(int dy);
    void setDx(int dx);
    void setZoom(int zoom);
    void setBackgroundColor(const QColor &backgroundColor);
    void setLineColor(const QColor &lineColor);
    void setGraphBackgroundColor(const QColor &graphBackgroundColor);
    void setGraphLineColor(const QColor &graphLineColor);

signals:
    void valueChanged();
public slots:


};

#endif // FRAMEPAINTER_H
