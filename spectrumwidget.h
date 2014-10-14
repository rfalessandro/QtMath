#ifndef SPECTRUMWIDGET_H
#define SPECTRUMWIDGET_H

#include <QWidget>
#include "graphwidget.h"
#include <complex.h>

typedef double complex cplx;

class SpectrumWidget : public GraphWidget
{
    Q_OBJECT

protected:
    void updateGraph();
    void paintEvent(QPaintEvent *);
    double binConst;
public:
    explicit SpectrumWidget(QWidget *parent = 0);
    void setBinConst(double value);
    double getBinConst() const;
    void setBuffer(const cplx *buffer, unsigned int szBuffer, unsigned int sampleRate);
signals:

public slots:

};

#endif // SPECTRUMWIDGET_H
