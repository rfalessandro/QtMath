#include "soundspleet.h"
#include "stdlib.h"
#include "soundutil.h"
#include <string.h>

SoundSpleet::~SoundSpleet()
{
    clear();
}



SoundSpleet::SoundSpleet()
{
    buf = NULL;
    szBuff  = NULL;
    count = 0;
}

int SoundSpleet::getCount() const
{
    return count;
}
unsigned char *SoundSpleet::getBuffer(int pos, int *sz)
{
    if(buf != NULL && pos >= count) {
        return NULL;
    }
    *sz = szBuff[pos];
    return buf[pos];
}

void SoundSpleet::split(unsigned char *buffer, unsigned int n, int nChannel, int bitDepth)
{
    clear();
    int szFrame = (nChannel * bitDepth);
    unsigned int sz = n/szFrame;
    unsigned int i = 0,j = 0;
    unsigned int *arrSplitPos = (unsigned int *)calloc(sizeof(unsigned int), sz);
    unsigned int itSpliPos = 0;
    arrSplitPos[itSpliPos++] = 0;
    for (i = 0; i < sz ; i++) {
        int value = SoundUtil::getIntValue(buffer, j, bitDepth);
        if(i == sz/2) {
            arrSplitPos[itSpliPos++] = j;
        }
        j += (nChannel * bitDepth);
    }

    if(itSpliPos > 0) {
        if(arrSplitPos[itSpliPos] < n)  {
            arrSplitPos[itSpliPos++] = n - 1;
        }
        buf = (unsigned char **)calloc(sizeof(unsigned char *), itSpliPos-1);
        szBuff = (unsigned int *)calloc(sizeof(unsigned int), itSpliPos-1);


        for(i =0; i< itSpliPos - 1; i++) {
            unsigned int lastPos = arrSplitPos[i];
            unsigned int pos = arrSplitPos[i+1];
            unsigned int szPos =  ( pos - lastPos);
            buf[i] = (unsigned char *)calloc(sizeof(unsigned char), szPos);
            memcpy(buf[i], buffer + lastPos, szPos );
            lastPos = pos;
            szBuff[i] = szPos;
        }

    }
    count = itSpliPos - 1;
    free(arrSplitPos);
}

void SoundSpleet::clear()
{
    if(buf != NULL) {
        if(szBuff != NULL) {
            for(int i =0; i< count; i++) {
                free(buf[i]);
            }
            free(szBuff );
            szBuff = NULL;
        }
        free(buf);
        buf = NULL;
    }
    count = 0;
}
