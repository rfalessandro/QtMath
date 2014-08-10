#ifndef SOUND_H
#define SOUND_H

#include <alsa/asoundlib.h>
#include <QThread>

class Sound : public QObject
{
private:
    int sampleRate;
    int bitDepth;
    int nChannel;
    long time;
    char *buffer;
    int szBuffer;
    int error;
    bool playing;
    QThread *thread;
protected:
    void run();
public:
    Sound();

    void setTime(long time);
    void setSampleRate(int sampleRate);
    void setBitDepth(int depth);
    void setNChannel(int nChannel);
    int getSampleRate();
    int getBitDepth();
    int getNChannel();

    void setBuffer(char *buffer, int szBuffer);

    long getTime();
    void play();
    void pause();
    void stop();
    bool isPlaying();

signals:
    Q_SLOT void stopSound();
    Q_SLOT void startSound();


};

#endif // SOUND_H
