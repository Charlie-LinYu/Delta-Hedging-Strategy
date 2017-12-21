#ifndef GetOption_H_INCLUDED
#define GetOption_H_INCLUDED
#include <map>
#include <string>
#include "Option.h"

/*
establish objects of the option class with different stock prices, 
market prices of options and risk-free rates regrading different dates,
map pointers to these option objects with date
*/
std::map<std::string, Option*> GetOption(Option *tmp_opt, double strike, std::map<std::string, double>& stock, double time,
	std::map<std::string, double>& interest, double ini_vol, double d,
	std::map<std::string, double>& opt_price, bool c);

#endif // GetOption_H_INCLUDED