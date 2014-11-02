#ifndef WAVEWIDGET_H
#define WAVEWIDGET_H

#include <QWidget>
#include "graphwidget.h"

class WaveWidget : public GraphWidget
{
    Q_OBJECT
protected:
    void updateGraph();
    void paintEvent(QPaintEvent *);
    int szSample;
    void createPoly(unsigned const char *buffer, unsigned int szBuffer,  int bitDepth, int nChannel, bool reset);
public:
    explicit WaveWidget(QWidget *parent = 0);
    void setBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate);
    void pushBuffer(unsigned const char *buffer, unsigned int szBuffer, int bitDepth, int nChannel, int sampleRate);

signals:

public slots:

};

#endif // WAVEWIDGET_H
