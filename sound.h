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

    bool playing;
    void getPlaybackDeviceList();
    vector<QString> lsPcmPlayback;
    vector<QString> lsPcmCapture;
    char *deviceName;
public:
    Sound();    
    static const int ERROR_OPEN_DEVICE = 1;
    static const int ERROR_PARAMS_DEVICE = 2;
    string *error;
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
    void progress(unsigned int value, double sec, const char  *info);
    void errorSignal(int type, const QString &errorStr);

};

#endif // SOUND_H
