#include "sound.h"
#include <alsa/asoundlib.h>
#include <QString>
#include <math.h>
#include <QString>
#include <QStringList>

Sound::Sound()
{
    sampleRate = 44100;
    nChannel = 2;
    bitDepth = 2;
    time = 1;
    deviceName = NULL;
    szBuffer = 0;
    setDeviceName("default");
    getPlaybackDeviceList();

}

void Sound::getPlaybackDeviceList()
{
    void **hints, **n;
    char *name, *descr, *io;

    if (snd_device_name_hint(-1, "pcm", &hints) < 0)
        return;
    n = hints;


    io = NULL;
    while (*n != NULL) {
        name = snd_device_name_get_hint(*n, "NAME");
        descr = snd_device_name_get_hint(*n, "DESC");
        io = snd_device_name_get_hint(*n, "IOID");
        if (strcmp("null", name) != 0)  {
            if(io == NULL) {
                lsPcmPlayback.push_back(QString(name));
                lsPcmCapture.push_back(QString(name));
            }else if(strcmp(io, "Output") == 0) {
                lsPcmPlayback.push_back(QString(name));
            }else if(strcmp(io, "Input") == 0) {
                lsPcmCapture.push_back(QString(name));
            }

        }else {
            if (name != NULL)
                free(name);
            if (descr != NULL)
                free(descr);
            if (io != NULL)
                free(io);
        }        
        n++;

    }
    snd_device_name_free_hint(hints);
}

void Sound::setBitDepth(int bitDepth)
{
    this->bitDepth = bitDepth;
}

void Sound::setNChannel(int nChannel)
{
    this->nChannel = nChannel;
}

void Sound::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
}

void Sound::setTime(long time)
{
    this->time = time;
}

void Sound::setDeviceName(const char *deviceName)
{
    if(this->deviceName != NULL) {
        free(this->deviceName);
    }
    int sz = strlen(deviceName) + 1;
    this->deviceName = (char *) malloc(sizeof(char) * sz);
    strcpy(this->deviceName, deviceName);
    this->deviceName[sz-1] = '\0';
}


int Sound::getBitDepth()
{
    return this->bitDepth;
}

int Sound::getNChannel()
{
    return this->nChannel;
}

int Sound::getSampleRate()
{
    return this->sampleRate;
}

long Sound::getTime()
{
    return this->time;
}


void Sound::setBuffer(unsigned const char *buffer, unsigned int sz)
{
    this->buffer = buffer;
    this->szBuffer = sz;
}

void Sound::run() {
    playing = true;


    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    long loops;
    int rc;
    int size;

    int dir;
    char *bufferToPlay;
    QString str = "";
    unsigned int desloc;

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&handle, this->deviceName, SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
        QString strError("Unable to open pcm device: ");
        strError.append(snd_strerror(rc));
        emit errorSignal(ERROR_OPEN_DEVICE, strError);
        stop();
        return;
    }


    /* Allocate a hardware parameters object. */
    snd_pcm_hw_params_alloca(&params);
    /* Fill it in with default values. */
    snd_pcm_hw_params_any(handle, params);

    /* Set the desired hardware parameters. */
    /* Interleaved mode */
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);


    /* Signed 16-bit little-endian format */
    switch(this->bitDepth ) {
    case 4:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S32_LE);
        break;
    case 3:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_LE);
        break;
    case 2:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
        break;
    case 1:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S8);
        break;

    }


    /* Two channels (stereo) */
    snd_pcm_hw_params_set_channels(handle, params, this->nChannel);

    /* 44100 bits/second sampling rate (CD quality) */
    unsigned int rate = this->sampleRate;
    snd_pcm_hw_params_set_rate_near(handle, params, &rate, &dir);



    /* Set period size to 32 frames. */
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);


    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
        QString strError("Unable to set hardware parameters: ");
        strError.append(snd_strerror(rc));
        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        emit errorSignal(ERROR_PARAMS_DEVICE , strError);
        stop();
        return ;
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(params, &frames,&dir);



    size = frames * this->nChannel * this->bitDepth;
    bufferToPlay = (char *) malloc(size);


    unsigned int peridTime;

    snd_pcm_hw_params_get_period_time(params,&peridTime, &dir);


    desloc = 0;
    loops = this->time / peridTime;
    unsigned int it = 0;
    emit startSound();

    while (it < loops  && playing) {
        str.clear();
        memcpy(bufferToPlay, buffer+desloc, size);
        desloc += size;
        if(desloc > szBuffer ) {
            desloc = 0;//circular
        }

        rc = snd_pcm_writei(handle, bufferToPlay, frames);
        if (rc == -EPIPE) {
            /* EPIPE means underrun */
            str.sprintf( "underrun occurred\n");
            snd_pcm_prepare(handle);
        } else if (rc < 0) {
            str.sprintf("error from writei: %s\n",snd_strerror(rc));
        }  else if (rc != (int)frames) {
            str.sprintf("short write, write %d frames\n", rc);
        }
        it++;
        emit progress(desloc, (((double)peridTime) * (double)it)/1000000.0, str.toStdString().c_str());
    }
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(bufferToPlay);
    stop();
    return;
}



void Sound::play()
{
    this->error = NULL;
    run();
}

void Sound::stop()
{
    if(playing) {
        playing = false;
        emit stopSound();
    }
}

bool Sound::isPlaying()
{
    return playing;
}

void Sound::pause()
{
    return ;
}

void Sound::process()
{
    run();
}


vector<QString> *Sound::getPlaybackList() const {
    return (vector<QString> *)&lsPcmPlayback;
}
