#ifndef Hedging_H_INCLUDED
#define Hedging_H_INCLUDED
#include <map>
#include <string>
#include <vector>
#include "Option.h"

class Hedging
{
private:
	//store all information of the delta hedging portfolio
	std::vector<std::string> date;
	std::vector<double> stocks;          //stock prices
	std::vector<double> qp;              //market prices of options(quoted price)
	std::vector<double> risk_free;
	std::vector<double> implied_vol;     //implied volatility
	std::vector<double> delta;
	std::vector<double> HE;              //hedging error
	std::vector<double> CHE;             //cumulative hedging error
	std::vector<double> PNL;             //profit and loss
	std::vector<double> B_new;           //cash position used to calculate cumulative hedging error
	std::vector<double> B_old;           //cash position usde to calculate hedging error
public:
	Hedging(std::map<std::string, Option*>& opt);      //constructor
	void print_out(const std::string& filename);       //print out csv file
};


#endif // Hedging_H_INCLUDED