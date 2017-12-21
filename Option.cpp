#include "Option.h"
#include <math.h>
//#include <boost/math/distributions/normal.hpp>

Option:: Option(double strike, double current, double time, double risk_free, double volatility, double dividend, bool c):
    k(strike), s(current), t(time), r(risk_free), sigma(volatility), q(dividend), call(c){}

void Option:: NewCurrentPrice(double current)
{
    s = current;
}

void Option::NewTime(double time)
{
	t = time;
}

double Option::BS()
{
	double d1, d2, v;
	//boost::math::normal nor(0, 1);
	d1 = (log(s / k) + (r - q + 0.5 * sigma * sigma) * t) / (sigma * sqrt(t));
	d2 = d1 - sigma * sqrt(t);
	if (call)
	{
		//v = s * exp(-q * t) * (boost::math::cdf(nor, d1)) - k * exp(-r * t) * (boost::math::cdf(nor, d2));
		v = s * exp(-q * t) * N(d1) - k * exp(-r * t) * N(d2);
	}
	else
	{
		//v = -s * exp(-q * t) * (boost::math::cdf(nor, -d1)) + k * exp(-r * t) * (boost::math::cdf(nor, -d2));
		v = -s * exp(-q * t) * N(-d1) + k * exp(-r * t) * N(-d2);
	}
	return v;
}

double Option::delta()
{
	double d1;
	//boost::math::normal nor(0, 1);
	d1 = (log(s / k) + (r - q + 0.5 * sigma * sigma) * t) / (sigma * sqrt(t));
	if(call){ return N(d1); }
	else{ return (N(d1) - 1); }
}

