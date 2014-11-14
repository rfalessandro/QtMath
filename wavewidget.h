#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QWidget>
#include "graphwidget.h"

class WaveWidget : public GraphWidget
{
    Q_OBJECT
protected:
    void resizeEvent(QResizeEvent *);
    void updateGraph();
    void paintEvent(QPaintEvent *);
    int szSample;
    double zoomConst;
    void createPoly(unsigned const char *buffer, unsigned int szBuffer,  int bitDepth, int nChannel, bool reset);

public:
    explicit WaveWidget(QWidget *parent = 0);
    void setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate, double time);
    void pushBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate, double time);

signals:

public slots:

};

#endif // WAVEWIDGET_H
