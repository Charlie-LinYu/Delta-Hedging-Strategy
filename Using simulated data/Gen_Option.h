#ifndef Gen_Option_H_INCLUDED
#define Gen_Option_H_INCLUDED
#include <vector>
#include "Option.h"

//generate the option vector regarding different current stock prices
std::vector<Option> Gen_Option(double strike, std::vector<double>& current, double expire, double delta_t, double r, double vol, double q, bool c);

#endif // Gen_Option_H_INCLUDED

