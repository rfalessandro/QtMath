#include "mathutil.h"

#include <stdlib.h>
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
        unsigned int ret = ( (  (0x000000FF & arr[pos + 0])  << 0) | (  (0x000000FF & arr[pos + 1]) << 8  ) |
                (  (0x000000FF & arr[pos + 2]) << 16 ) | (  (0x000000FF & arr[pos + 3]) << 24 ) );
        return (int32_t)ret;
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

