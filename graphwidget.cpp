#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    backgroundColor = QColor( 0x22,0x33,0x55, 0xFF);
    graphLineColor = QColor(0x44, 0x88, 0x33, 0xFF);
    graphBackgroundColor = QColor(0x44, 0x88, 0x33, 0x88);
    lineColor = QColor(0xFF, 0xFF, 0xFF, 0xFF);
    dx = 0;
    dy = 0;
    zoom = 1;

    lsPy = NULL;

}




QColor GraphWidget::getBackgroundColor()
{
    return this->backgroundColor;
}

QColor GraphWidget::getLineColor()
{
    return this->lineColor;
}


QColor GraphWidget::getGraphBackgroundColor()
{
    return this->graphBackgroundColor;
}

QColor GraphWidget::getGraphLineColor()
{
    return this->graphLineColor;
}


int GraphWidget::getDy() const
{
    return this->dy;
}

int GraphWidget::getDx() const
{
    return this->dx;
}

double GraphWidget::getZoom() const
{
    return this->zoom;
}



void GraphWidget::setDy(int dy)
{
    if(this->dy != dy) {
        this->dy = dy;
        emit valueChanged();
        updateGraph();
    }
}



void GraphWidget::setDx(int dx)
{
    if(this->dx != dx) {
        this->dx = dx;
        emit valueChanged();
        updateGraph();
    }
}

void GraphWidget::setZoom(double zoom)
{
    if(this->zoom != zoom) {
        this->zoom = zoom;
        emit valueChanged();
        updateGraph();
    }
}

void GraphWidget::setBackgroundColor(const QColor &backgroundColor)
{
    if(this->backgroundColor != backgroundColor) {
        this->backgroundColor = backgroundColor;
        updateGraph();
    }
}

void GraphWidget::setLineColor(const QColor &lineColor)
{
    if(this->lineColor != lineColor) {
        this->lineColor = lineColor;
        updateGraph();
    }
}



void GraphWidget::setGraphBackgroundColor(const QColor &graphBackgroundColor)
{
    if(this->graphBackgroundColor != graphBackgroundColor) {
        this->graphBackgroundColor = graphBackgroundColor;
        updateGraph();
    }
}

void GraphWidget::setGraphLineColor(const QColor &graphLineColor)
{
    if(this->graphLineColor != graphLineColor) {
        this->graphLineColor = graphLineColor;
        updateGraph();
    }
}


void GraphWidget::pushPy(int py)
{
    if(this->lsPy == NULL) {
        this->lsPy = new QList<int>();
    }
    this->lsPy->push_back(py);
}
void GraphWidget::setLsPy(QList<int> *lsPy)
{
    this->lsPy = lsPy;
}

int GraphWidget::getPy(int pos) const
{
    if(this->lsPy != NULL && this->lsPy->length() > pos)     {
        return lsPy->at(pos);
    }
    return 0;

}

QList<int> *GraphWidget::getLsPy() const{
    return this->lsPy;
}



void GraphWidget::updateGraph()
{

}

void GraphWidget::paintEvent(QPaintEvent *)
{

}
