#include "sound.h"
#include <alsa/asoundlib.h>
#include <QString>
#include <math.h>


Sound::Sound()
{
    sampleRate = 44100;
    nChannel = 2;
    bitDepth = 2; 
    time = 1;

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

    this->error = 0;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    snd_pcm_uframes_t frames;
    long loops;
    int rc;
    int size;
    unsigned int val;
    unsigned int val2;
    int dir;
    char *bufferToPlay;
    QString str = "";
    unsigned int desloc;

    /* Open PCM device for playback. */
    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0) {
      str.sprintf("unable to open pcm device: %s\n",   snd_strerror(rc));
      this->error = 1;
      stop();
      return;

    }
    QString info="";
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
    val = this->sampleRate;
    snd_pcm_hw_params_set_rate_near(handle, params,&val, &dir);

    info.sprintf(" Rate: %d hz , ", val);

    /* Set period size to 32 frames. */
    frames = 32;
    snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);


    /* Write the parameters to the driver */
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) {
      str.sprintf("unable to set hw parameters: %s\n", snd_strerror(rc));
      this->error =  -1;
      stop();
      return ;
    }

    /* Use a buffer large enough to hold one period */
    snd_pcm_hw_params_get_period_size(params, &frames,&dir);
    info.sprintf(" Period Size: %d  , ", (int)frames);


    size = frames * this->nChannel * 2; /* 2 bytes/sample, 2 channels */
    bufferToPlay = (char *) malloc(size);

    info.sprintf(" bufferToPlay Size: %d  , ", size);


    /* We want to loop for 5 seconds */
    snd_pcm_hw_params_get_period_time(params,&val2, &dir);
    /* 5 seconds in microseconds divided by
    * period time */

    info.sprintf(" Period Time: %d  , ", val2);


    desloc = 0;
    loops = this->time / val2;
    unsigned int it = 0;
    emit startSound();
    while (it < loops  && playing) {

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
        emit progress(desloc, (((double)val2) * (double)it)/1000000.0);
    }
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(bufferToPlay);
    this->error =  0;
    stop();
    return;
}



void Sound::play()
{
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
