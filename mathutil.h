#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <stdlib.h>

class MathUtil
{

public:
    MathUtil();

    static unsigned char *to32Le(uint value);
    static unsigned char *to24Le(uint value);
    static unsigned char *to16Le(uint value);
    static unsigned char *to8Le(uint value);

    static int32_t  to32Le(const unsigned char *arr, int pos);
    static int32_t to24Le(const unsigned char *arr, int pos);
    static int16_t to16Le(const unsigned char *arr, int pos);
    static int8_t  to8Le(const unsigned char *arr, int pos);





};

#endif // MATHUTIL_H
