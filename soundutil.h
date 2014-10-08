#ifndef SOUNDUTIL_H
#define SOUNDUTIL_H

#include <complex.h>

typedef double complex cplx;

class Soundutil
{
public:
    Soundutil();

    static int getIntValue(const unsigned char *buffer, int pos, int  bitDepth);
    static unsigned char *getCharValue(int value, int  bitDepth);
    static cplx *toComplex(const unsigned char * buffer, unsigned int *n, int nChannel, int bitDepth, int channel) ;
    static unsigned char *toBuffer(const cplx *buffer, unsigned int *n, int sampleRate, int nChannel, int bitDepth) ;

};

#endif // SOUNDUTIL_H
