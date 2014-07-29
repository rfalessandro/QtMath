#ifndef SOUND_H
#define SOUND_H

#include <alsa/asoundlib.h>
#include <QThread>

class Sound : private QThread
{
private:
    int sampleRate;
    int bitDepth;
    int nChannel;
    long time;
    char *buffer;
    int szBuffer;
    int error;
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
    int play();
    int pause();
    int stop();


};

#endif // SOUND_H
