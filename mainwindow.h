#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialogmakegraph.h"
#include <QMainWindow>
#include <audioscene.h>
#include <sound.h>
#include <QThread>
#include "rawinfodialog.h"
#include "spectrumwidget.h"
namespace Ui {
class MainWindow;
}

using namespace std;

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
    SpectrumWidget *spectrumWidget;
    QThread *threadSound;
    Sound *sound;
    unsigned char *buffer;
    unsigned int szBuffer;
    int sampleRate;
    int nChannel;
    int bitDepth;
    RawInfoDialog *rawInfoDlg;
    DialogMakeGraph *graphDlg;
    void updateSoundInfo();
private slots:
    void open();
    void openMakeGraph();
    void save();
    void recalc();
    void updateMain();
    void recordSound();
    void playSound();
    void makeGraph();
    void updateFrame();
    void soundError(int errorType, const QString &errorStr);
    void soundStatus();
    void soundProgess(unsigned int value, double sec, const char *);
    void acceptRawInfo();
    void changeDevice();
};


#endif // MAINWINDOW_H
