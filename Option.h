#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include "StdNormalCDF.h"

class Option
{
private:
	//k = strike price, s = current stock price, t = time to expiration, r = risk-free rate,
	//sigma = volatility, q = dividend rate
    double k, s, t, r, sigma, q;   
	bool call;
	StdNormalCDF N;         //N is used to calcualte the cdf of a standard normal distrubution
public:
    Option(double strike, double current, double time, double risk_free, double volatility, double dividend, bool c);
    void NewCurrentPrice(double current);   //change the current price of the underlying stock
	void NewTime(double time);              //change the time to expiration          
    double BS();                            //return the option price based on BS model
	double delta();                         //return the delta of an option
}; 

#endif // OPTION_H_INCLUDED
