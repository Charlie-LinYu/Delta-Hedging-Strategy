#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED
#include "StdNormalCDF.h"
#include <iostream>

class Option
{
private:
	//k = strike price, s = current stock price, t = time to expiration, r = risk-free rate,
	//sigma = volatility, q = dividend rate
	double k, s, t, r, sigma, q, real_p;
	bool call;
	StdNormalCDF N;            //N is used to calcualte the cdf of a standard normal distrubution
public:
	Option();                  //default constructor used for the new operator

	//constructor
	Option(double strike, double current, double time, double risk_free, double volatility, double dividend, double real_p, bool c);
	
	//update all information of an option class, similar to the constructor but avoid uncessary initialization
	void Update(double strike, double current, double time, double risk_free, double volatility, double dividend, double qp, bool c);
	
	const double BS();                         //return the option price based on BS model
	const double delta();                      //return the delta of an option
	const double vega();                       //return the vega
	const double get_implied_vol();            //return the implied volatility
	const double get_underlying();             //return the current underlying stock price
	const double get_real_price();             //return the current market price of the option
	const double get_risk_free();              //return the current risk-free rate
	friend std::ostream& operator<<(std::ostream& os, const Option& opt);
};



#endif // OPTION_H_INCLUDED