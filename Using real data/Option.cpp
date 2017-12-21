#include "Option.h"
#include "StdNormalCDF.h"
#include <math.h>
#include <cmath>
//#include <boost/math/distributions/normal.hpp>

//default constructor
Option::Option()
{
	k = 0; s = 0; t = 0; r = 0; sigma = 0; q = 0; real_p = 0; call = true;
}

Option::Option(double strike, double current, double time, double risk_free, double volatility, double dividend, double qp, bool c) :
	k(strike), s(current), t(time), r(risk_free), sigma(volatility), q(dividend), real_p(qp), call(c) {}

void Option::Update(double strike, double current, double time, double risk_free, double volatility, double dividend, double qp, bool c)
{
	k = strike; s = current; t = time; r = risk_free; sigma = volatility; q = dividend; real_p = qp; call = c;
}

const double Option::BS()
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

const double Option::delta()
{
	double d1;
	//boost::math::normal nor(0, 1);
	d1 = (log(s / k) + (r - q + 0.5 * sigma * sigma) * t) / (sigma * sqrt(t));
	if (call) {
		//return boost::math::cdf(nor, d1);
		return N(d1);
	}
	else {
		//return boost::math::cdf(nor, d1) - 1;
		return (N(d1) - 1);
	}
}

const double Option::vega()
{
	double d1, v;
	//boost::math::normal nor(0, 1);
	d1 = (log(s / k) + (r - q + 0.5 * sigma * sigma) * t) / (sigma * sqrt(t));
	//v = s * sqrt(t) * (boost::math::pdf(nor, d1));
	v = s * sqrt(t) * (1/sqrt(2.0*3.1415926)*exp(-d1*d1/2));
	return v;
}

//use newtom method to calculate the implied volatility
//const double Option::get_implied_vol()
//{
//	for (int i = 0; i < 5000; i++)
//	//while(1)
//	{
//		if (fabs(BS() - real_p) < 0.0001) { break; }
//		else
//		{
//			sigma = sigma + (real_p - BS()) / vega();
//		}
//	}
//	return sigma;
//}

//use binary search to calculate hte implied volatility
const double Option::get_implied_vol()
{
	double min_vol = 0.0;
	double max_vol = sigma;
	double half = (min_vol + max_vol) / 2;
	//while (1)
	for (int i =0;i<5000;i++)
	{
		sigma = half;
		if (fabs(BS() - real_p) <= 0.0001) { break; }
		else if (BS() > real_p)
		{
			max_vol = half;
			min_vol = min_vol;
			half = (min_vol + max_vol) / 2;
		}
		else
		{
			max_vol = max_vol;
			min_vol = half;
			half = (min_vol + max_vol) / 2;
		}
	}
	return sigma;
}

const double Option::get_underlying()
{
	return s;
}

const double Option::get_real_price()
{
	return real_p;
}

const double Option::get_risk_free()
{
	return r;
}

