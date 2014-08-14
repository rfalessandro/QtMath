#ifndef SOUND_H
#define SOUND_H

#include <alsa/asoundlib.h>
#include <QObject>

class Sound : public QObject
{
    Q_OBJECT
protected:
    void run();

private:
    int sampleRate;
    int bitDepth;
    int nChannel;
    long time;
    unsigned const char *buffer;
    int szBuffer;
    int error;
    bool playing;
public:
    Sound();    
    void setTime(long time);
    void setSampleRate(int sampleRate);
    void setBitDepth(int depth);
    void setNChannel(int nChannel);
    int getSampleRate();
    int getBitDepth();
    int getNChannel();

    void setBuffer(unsigned const char *buffer, int szBuffer);

    long getTime();
    void play();
    void pause();
    void stop();
    bool isPlaying();

public slots:
    void process() ;
signals:
    void stopSound();
    void startSound();


};

#endif // SOUND_H
