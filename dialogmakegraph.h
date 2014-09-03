#ifndef DIALOGMAKEGRAPH_H
#define DIALOGMAKEGRAPH_H

#include <QDialog>

namespace Ui {
class DialogMakeGraph;
}

class DialogMakeGraph : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMakeGraph(QWidget *parent = 0);
    ~DialogMakeGraph();
    unsigned char *getGraph();
    int getBitDepth();
    int getSampleRate();
    int getFrequency();
    int getNChannel();
    int getAmplitude();
private:
    Ui::DialogMakeGraph *ui;

public slots:

signals:
    void graphCreated();

};

#endif // DIALOGMAKEGRAPH_H
