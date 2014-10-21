#include "statisticutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <soundutil.h>
#include <string.h>
#include <complex.h>
#include <math.h>
#include <algorithm>


StatisticUtil::StatisticUtil()
{
}

cplx StatisticUtil::getMaxMaginitude(const cplx *buf, unsigned int n)
{

    double maxY = 0;
    unsigned int pos = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = creal(buf[i]);
        double d2 = cimag(buf[i]);
        double d3 = ( sqrt(pow(d1,2) + pow(d2,2)) );
        if(d3 > maxY) {
            maxY =  d3;
            pos = i;
        }
    }
    return buf[pos];
}

cplx StatisticUtil::getMinMaginitude(const cplx *buf, unsigned int n)
{
    double minY = 0;
    unsigned int pos = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = creal(buf[i]);
        double d2 = cimag(buf[i]);
        double d3 = ( sqrt(pow(d1,2) + pow(d2,2)) );
        if(d3 < minY) {
            minY =  d3;
            pos = i;
        }
    }
    return buf[pos];

}

double StatisticUtil::getMaxReal(const cplx *buf, unsigned int n)
{
    double maxY = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = creal(buf[i]);
        if(d1 > maxY) {
            maxY =  d1;
        }
    }
    return maxY;
}

double StatisticUtil::getMinReal(const cplx *buf, unsigned int n)
{
    double minY = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = creal(buf[i]);
        if(d1 < minY) {
            minY =  d1;
        }
    }
    return minY;
}

double StatisticUtil::getMaxImaginary(const cplx *buf, unsigned int n)
{
    double maxY = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = cimag(buf[i]);
        if(d1 > maxY) {
            maxY =  d1;
        }
    }
    return maxY;
}

double StatisticUtil::getMinImaginary(const cplx *buf, unsigned int n)
{
    double minY = 0;
    for(unsigned int i = 0 ;i < n; i++) {
        double d1 = cimag(buf[i]);
        if(d1 < minY) {
            minY =  d1;
        }
    }
    return minY;
}
