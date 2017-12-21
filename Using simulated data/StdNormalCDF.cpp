#include "StdNormalCDF.h"
#include <math.h>

const double StdNormalCDF::A1 = 0.319381530;
const double StdNormalCDF::A2 = -0.356563782;
const double StdNormalCDF::A3 = 1.781477937;
const double StdNormalCDF::A4 = -1.821255978;
const double StdNormalCDF::A5 = 1.330274429;
const double StdNormalCDF::B = 0.2316419;
const double StdNormalCDF::NORMALIZER = 0.39894220;

const double StdNormalCDF:: operator() (double x)
{
    if (x < 0)
    {
        return (1 - (*this)(-x));
    }
    double z = 1.0 / (1 + B * x);
    double R = A1 * z + A2 * pow(z,2) + A3 * pow(z,3) + A4 * pow(z,4) + A5 * pow(z,5);
    double N = 1.0 - NORMALIZER * exp(-x * x / 2) * R;
    return N;
}

