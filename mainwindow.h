#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialogmakegraph.h"
#include <QMainWindow>
#include <audioscene.h>
#include <sound.h>
#include <QThread>
#include "rawinfodialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AudioScene *tela;
    QThread *t;
    Sound *sound;
    unsigned char *buffer;
    unsigned int szBuffer;
    int sampleRate;
    int nChannel;
    int bitDepth;
    RawInfoDialog *rawInfoDlg;
    DialogMakeGraph *graphDlg;

private slots:
    void open();
    void openMakeGraph();
    void save();
    void recalc();
    void updateMain();
    void playSound();
    void makeGraph();
    void updateFrame();
    void soundStatus();
    void soundProgess(unsigned int value, double sec);
    void acceptRawInfo();
};


#endif // MAINWINDOW_H
