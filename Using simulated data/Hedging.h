#ifndef Hedging_H_INCLUDED
#define Hedging_H_INCLUDED
#include "Option.h"
#include <vector>

class Hedging
{
private:
	std::vector<double> stocks;             //store the stock prices
	std::vector<Option> options;            //store the options
	std::vector<double> B;                  //store the information of cash position
	std::vector<double> CHE;                //store the cumulative hedging error
public:
	Hedging(std::vector<double>st, std::vector<Option>op, double r, double delta_t);        //constructor
	void update(std::vector<double>st, std::vector<Option>op, double r, double delta_t);    //update the member variables to avoid initialization
	void print_out(const std::string filename);                  //output to a csv file
	double get_CHE();                                            //get the last element of CHE vector
};

#endif // Hedging_H_INCLUDED