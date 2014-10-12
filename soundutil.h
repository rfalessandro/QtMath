#ifndef SOUNDUTIL_H
#define SOUNDUTIL_H

#include <complex.h>

typedef double complex cplx;

class SoundUtil
{
public:
    SoundUtil();

    static int getIntValue(const unsigned char *buffer, int pos, int  bitDepth);
    static unsigned char *getCharValue(int value, int  bitDepth);
    static cplx *toComplex(const unsigned char * buffer, unsigned int *n, int nChannel, int bitDepth, int channel) ;
    static unsigned char *toBuffer(const cplx *buffer, unsigned int *n, int sampleRate, int nChannel, int bitDepth) ;

    static double indexToFrequency(int i, int sampleRate, int szFFT);
    static int frequencyToIndex(double freq, int sampleRate, int szFFT);
};

#endif // SOUNDUTIL_H
