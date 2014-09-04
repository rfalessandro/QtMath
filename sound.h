#ifndef SOUND_H
#define SOUND_H

#include <alsa/asoundlib.h>
#include <QObject>
#include <vector>

using namespace std;

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
    unsigned int szBuffer;
    int error;
    bool playing;
    void getPlaybackDeviceList();
    vector<QString> lsPcmPlayback;
    char *deviceName;
public:
    Sound();    
    void setTime(long time);
    void setSampleRate(int sampleRate);
    void setBitDepth(int depth);
    void setNChannel(int nChannel);
    int getSampleRate();
    int getBitDepth();
    int getNChannel();

    void setDeviceName(const char *deviceName);
    void setBuffer(unsigned const char *buffer, unsigned int szBuffer);

    long getTime();
    void play();
    void pause();
    void stop();
    bool isPlaying();

    vector<QString> *getPlaybackList() const;

public slots:
    void process() ;
signals:
    void stopSound();
    void startSound();
    void progress(unsigned int value, double sec);


};

#endif // SOUND_H
