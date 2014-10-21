#include "mathutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <soundutil.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <algorithm>
MathUtil::MathUtil()
{

}

unsigned char *MathUtil::to32Le(uint value)
{
    unsigned char *buffer;
    buffer = (unsigned char *)calloc(sizeof(unsigned char),  4);

    unsigned char d = (unsigned char) ( (value >> 24  )  & 0xFF );//pega os 8 bits do lado fim
    unsigned char c = (unsigned char) ( (value >> 16  )  & 0xFF );//pega os 8 bits do meio
    unsigned char b = (unsigned char) ( (value >> 8   )  & 0xFF );//pega os 8 bits do lado
    unsigned char a = (unsigned char) ( (value >> 0   )  & 0xFF );//pega os 8bits do fim
    buffer[0] = a;
    buffer[1] = b;
    buffer[2] = c;
    buffer[3] = d;
    return buffer;
}


unsigned char *MathUtil::to24Le(uint value)
{
    unsigned char *buffer;
    buffer = (unsigned char *)calloc(sizeof(unsigned char),  3);
    unsigned char c = (unsigned char) ( (value >> 16  )  & 0xFF );//pega os 8 bits do meio
    unsigned char b = (unsigned char) ( (value >> 8   )  & 0xFF );//pega os 8 bits do lado
    unsigned char a = (unsigned char) ( (value >> 0   )  & 0xFF );//pega os 8bits do fim
    buffer[0] = a;
    buffer[1] = b;
    buffer[2] = c;
    return buffer;
}


unsigned char *MathUtil::to16Le(uint value)
{
    unsigned char *buffer;
    buffer = (unsigned char *)calloc(sizeof(unsigned char),  2);
    unsigned char b = (unsigned char) ( (value >> 8   )  & 0xFF );//pega os 8 bits do lado
    unsigned char a = (unsigned char) ( (value >> 0   )  & 0xFF );//pega os 8bits do fim
    buffer[0] = a;
    buffer[1] = b;
    return buffer;
}



unsigned char *MathUtil::to8Le(uint value)
{
    unsigned char *buffer;
    buffer = (unsigned char *)calloc(sizeof(unsigned char),  1);
    unsigned char a = (unsigned char) ( (value >> 0   )  & 0xFF );//pega os 8bits do fim
    buffer[0] = a;
    return buffer;
}


int32_t MathUtil::to32Le(const unsigned char *arr, int pos)
{
    if(arr != NULL) {
        return ( (  (0x000000FF & arr[pos + 0])  << 0) | (  (0x000000FF & arr[pos + 1]) << 8  ) |
                (  (0x000000FF & arr[pos + 2]) << 16 ) | (  (0x000000FF & arr[pos + 3]) << 24 ) );
    }
    return 0;
}

int32_t MathUtil::to24Le(const unsigned char *arr, int pos)
{
    if(arr != NULL) {
        return ( (  (0x000000FF & arr[pos + 0])  << 0) | (  (0x000000FF & arr[pos + 1]) << 8  ) |
                (  (0x000000FF & arr[pos + 2]) << 16 )  );
    }
    return 0;
}

int16_t MathUtil::to16Le(const unsigned char *arr, int pos)
{
    if(arr != NULL) {
        return ( (  (0x000000FF & arr[pos + 0])  << 0) | (  (0x000000FF & arr[pos + 1]) << 8  )  );
    }
    return 0;
}

int8_t MathUtil::to8Le(const unsigned char *arr, int pos)
{
    if(arr != NULL) {
        return ( (  (0x000000FF & arr[pos + 0]) << 0)  );
    }
    return 0;
}

void MathUtil::_fft(cplx buf[], cplx out[], int n, int step)
{
    if (step < n) {
        _fft(out, buf, n, step * 2);
        _fft(out + step, buf + step, n, step * 2);

        for (int i = 0; i < n; i += 2 * step) {
            cplx t = cexp(-I * M_PI * i / n) * out[i + step];
            buf[i / 2]     = out[i] + t;
            buf[(i + n)/2] = out[i] - t;
        }
    }
}




cplx *MathUtil::fft(const unsigned char *buffer, unsigned int n, int nChannel, int bitDepth) {
    int n2 = pow(2, ceil(log2((double)n)) );

    cplx *out = (cplx *)calloc(sizeof(cplx), n2);
    cplx *buf = (cplx *)calloc(sizeof(cplx), n2);

    unsigned int i = 0,j = 0;
    for (i = 0; i < n; i++) {
        int value = SoundUtil::getIntValue(buffer, j, bitDepth);

        buf[i] = value;
        out[i] = value;
        j += (nChannel * bitDepth);
    }

     _fft(buf, out, n2 , 1);
    return buf;
}

cplx *MathUtil::fft(cplx *buffer, unsigned int n)
{
    int n2 = pow(2, ceil(log2((double)n)) );

    cplx *out = (cplx *)calloc(sizeof(cplx), n2);
    memcpy(out, buffer, sizeof(cplx) * n);

    _fft(buffer, out, n2, 1);

    return buffer;
}


void MathUtil::ifft(cplx *buf, unsigned int n) {

    cplx *out = (cplx *)calloc(sizeof(cplx), n);

    for(unsigned int i = 0 ;i < n; i++) {
        cplx aux = conj(buf[i]);
        buf[i] = aux;
        out[i] = aux;
    }

    _fft(buf, out, n, 1);

    for(unsigned int i = 0 ;i < n; i++) {
        buf[i] = conj(buf[i])/n;
    }
}

void MathUtil::addArray(cplx *buf, unsigned int n, const cplx *buf2, unsigned int n2)
{
    unsigned int szMin = std::min(n,n2);
    for(unsigned int i = 0 ;i < szMin; i++) {
        buf[i] += buf2[i];
    }
}

void MathUtil::subArray(cplx *buf, unsigned int n, const cplx *buf2, unsigned int n2)
{
    unsigned int szMin = std::min(n,n2);
    for(unsigned int i = 0 ;i < szMin; i++) {
        buf[i] -= buf2[i];
    }
}

void MathUtil::divArray(cplx *buf, unsigned int n,const cplx *buf2, unsigned int n2)
{
    unsigned int szMin = std::min(n,n2);
    for(unsigned int i = 0 ;i < szMin; i++) {
        buf[i] /= buf2[i];
    }
}

void MathUtil::multiArray(cplx *buf, unsigned int n, const cplx *buf2, unsigned int n2)
{
    unsigned int szMin = std::min(n,n2);
    for(unsigned int i = 0 ;i < szMin; i++) {
        buf[i] *= buf2[i];
    }
}

void MathUtil::addArray(cplx *buf, unsigned int n, const cplx value)
{
    for(unsigned int i = 0 ;i < n; i++) {
        buf[i] += value;
    }
}

void MathUtil::subArray(cplx *buf, unsigned int n, const cplx value)
{
    for(unsigned int i = 0 ;i < n; i++) {
        buf[i] -= value;
    }
}

void MathUtil::divArray(cplx *buf, unsigned int n, const cplx value)
{
    for(unsigned int i = 0 ;i < n; i++) {
        buf[i] /= value;
    }
}

void MathUtil::multiArray(cplx *buf, unsigned int n, const cplx value)
{
    for(unsigned int i = 0 ; i < n; i++) {
        buf[i] *= value;
    }
}





unsigned char *MathUtil::splitBuffer(const unsigned char *buffer, unsigned int posInit, unsigned int posEnd)
{
    unsigned int szPos =  ( posEnd - posInit);
    unsigned char *buf = (unsigned char *)calloc(sizeof(unsigned char), szPos);
    memcpy(buf, buffer + posInit, szPos );
    return buf;
}
