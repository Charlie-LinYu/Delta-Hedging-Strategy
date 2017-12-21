#ifndef Gen_Stock_H_INCLUDED
#define Gen_Stock_H_INCLUDED
#include <vector>

//generate the stock prices with normally distributed random numbers
std::vector<double> Gen_Stock(double seed, int times, double s0, double delta_t, double miu, double sigma);

#endif // Gen_Stock_H_INCLUDED
