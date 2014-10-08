#include "soundutil.h"
#include "mathutil.h"
#include <string.h>

Soundutil::Soundutil()
{
}



int Soundutil::getIntValue(const unsigned char *buffer, int pos, int bitDepth)
{
    int value;
    switch (bitDepth) {
        case 1:
            value = MathUtil::to8Le(buffer, pos);
            break;
        case 2:
            value = MathUtil::to16Le(buffer, pos);
            break;
        case 3:
            value = MathUtil::to24Le(buffer, pos);
            break;
        case 4:
            value = MathUtil::to32Le(buffer, pos);
            break;
        default:
            break;
    }
    return value;
}



unsigned char *Soundutil::getCharValue(int value, int  bitDepth)
{
    switch (bitDepth) {
        case 1:
            return MathUtil::to8Le(value);
            break;
        case 2:
            return MathUtil::to16Le(value);
            break;
        case 3:
            return MathUtil::to24Le(value);
            break;
        case 4:
            return MathUtil::to32Le(value);
            break;
        default:
            break;
    }
    return NULL;
}



cplx *Soundutil::toComplex(const unsigned char * buffer, unsigned int *n, int nChannel, int bitDepth, int channel)
{    
    int n2 = pow(2, ceil(log2((double)*n)) );
    cplx *out = (cplx *)calloc(sizeof(cplx), n2);    
    unsigned int i = 0,j = channel * bitDepth;
    for (i = 0; i < *n; i++) {
        out[i] = getIntValue(buffer, j, bitDepth);
        j += (nChannel * bitDepth);
    }
    *n = n2;
    return out;

}


unsigned char *Soundutil::toBuffer(const cplx *buffer, unsigned int *n, int sampleRate, int nChannel, int bitDepth)
{
    int szBuffer = (sampleRate * nChannel * bitDepth);
    unsigned char *out = (unsigned char *)calloc(sizeof(unsigned char), szBuffer);

    unsigned int j=0;
    unsigned char *aux = NULL;

    for(int i=0; i < sampleRate ; i++ ) {

        double d1 = creal(buffer[i]);
        double d2 = cimag(buffer[i]);

        int value = round( sqrt(pow(d1,2) + pow(d2,2) ));
        if(d1+d2< 0) {
            value = -value;
        }



        aux = getCharValue(value, bitDepth);

        for(int w=0; w < nChannel ; w++) {
            memcpy(out+j, aux, bitDepth);
            j += bitDepth;
        }
        if(aux != NULL)  {
            free(aux);
        }

    }
    *n = j;
    return out;

}
