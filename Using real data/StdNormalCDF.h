#ifndef STDNORMALCDF_H_INCLUDED
#define STDNORMALCDF_H_INCLUDED

class StdNormalCDF
{
private:
    static const double A1;
    static const double A2;
    static const double A3;
    static const double A4;
    static const double A5;
    static const double B;
    static const double NORMALIZER;
public:
    const double operator() (double x);
};

#endif // STDNORMALCDF_H_INCLUDED
