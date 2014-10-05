#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QList>
class GraphWidget : public QWidget
{
    Q_OBJECT
protected:
    void updateGraph();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *evt);
    void mouseMoveEvent(QMouseEvent *evt);
    void wheelEvent(QWheelEvent *evt);

    QPoint ptOld;
    QColor backgroundColor;
    QColor lineColor;
    QColor pointColor;
    QColor fontColor;
    QColor graphBackgroundColor;
    QColor graphLineColor;
    int dy;
    int dx;
    double zoom;

    QList<int> *lsPy;

    int xMax;
    int yMax;
    int deltaX;
    int deltaY;

public:
    explicit GraphWidget(QWidget *parent = 0);

    QColor getBackgroundColor();
    QColor getLineColor();
    QColor getPointColor();
    QColor getGraphBackgroundColor();
    QColor getGraphLineColor();
    int getDy() const;
    int getDx() const;
    QList<int> *getLsPy() const;
    int getPy(int pos) const;


    double getZoom() const;
    void clear();
    void pushPy(int py);
    void setLsPy(QList<int> *lsPy);
    void setBackgroundColor(const QColor &backgroundColor);
    void setLineColor(const QColor &lineColor);
    void setFontColor(const QColor &fontColor);
    void setPointColor(const QColor &graphLineColor);
    void setGraphBackgroundColor(const QColor &graphBackgroundColor);
    void setGraphLineColor(const QColor &graphLineColor);
    void setDy(int dy);
    void setDx(int dx);
    void setZoom(double zoom);

signals:
    void valueChanged();
public slots:


};

#endif // GRAPHWIDGET_H
