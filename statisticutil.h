#ifndef STATISTICUTIL_H
#define STATISTICUTIL_H

#include <complex.h>
typedef double complex cplx;

class StatisticUtil
{
public:
    StatisticUtil();


    static cplx getMaxMaginitude(const cplx *buff, unsigned int n);
    static cplx getMinMaginitude(const cplx *buff, unsigned int n);
    static double getMaxReal(const cplx *buff, unsigned int n);
    static double getMinReal(const cplx *buff, unsigned int n);
    static double getMaxImaginary(const cplx *buff, unsigned int n);
    static double getMinImaginary(const cplx *buff, unsigned int n);
};

#endif // STATISTICUTIL_H
