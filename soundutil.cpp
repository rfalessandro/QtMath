#include "soundutil.h"
#include "mathutil.h"


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


cplx *Soundutil::toComplex(const unsigned char * buffer, unsigned int *n, int nChannel, int bitDepth)
{
    int n2 = pow(2, ceil(log2((double)*n)) );
    cplx *out = (cplx *)calloc(sizeof(cplx), n2);
    unsigned int i = 0,j = 0;
    for (i = 0; i < *n; i++) {
        out[i] = getIntValue(buffer, j, bitDepth);
        j += (nChannel * bitDepth);
    }
    *n = n2;
    return out;

}
