#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <framepainter.h>
#include <sound.h>
#include <QThread>


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
    FramePainter *tela;
    QThread *t;
    Sound *sound;
    unsigned char *buffer;
    int szBuffer;
    int sampleRate;
    int nChannel;
    int bitDepth;

private slots:
    void recalc();
    void updateMain();
    void playSound();
    void makeGraph();
    void updateFrame();
    void soundStatus();
};


#endif // MAINWINDOW_H
