#include "mathutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <soundutil.h>
#include <string.h>
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
    //int n2 = n;

    cplx *out = (cplx *)calloc(sizeof(cplx), n2);
    cplx *buf = (cplx *)calloc(sizeof(cplx), n2);

    unsigned int i = 0,j = 0;
    for (i = 0; i < n; i++) {
        int value = Soundutil::getIntValue(buffer, j, bitDepth);
        buf[i] = value;
        out[i] = value;
        j += (nChannel * bitDepth);
    }

    _fft(buf, out, n2 , 1);
    return buf;
}

cplx *MathUtil::fft(cplx *buffer, unsigned int n) {

    int n2 = pow(2, (int)( log2((double)n) + 0.5 ));
    //int n2 = n;

    cplx *out = (cplx *)calloc(sizeof(cplx), n2);

    unsigned int i = 0;

    for (i = 0; i < n; i++) {
        out[i] = buffer[i];
    }
    _fft(buffer, out, n2, 1);

    return buffer;
}

