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



