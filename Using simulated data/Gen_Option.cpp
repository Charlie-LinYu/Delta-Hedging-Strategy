#include "Gen_Option.h"

std::vector<Option> Gen_Option(double strike, std::vector<double>& current, double expire, double delta_t, double r, double vol, double q, bool c)
{
	Option tmp_option(strike, current[0], expire, r, vol, q, c);  //initilize an option class
	std::vector<Option> opt;
	opt.push_back(tmp_option);
	for (int i = 1; i < current.size(); i++)
	{
		tmp_option.NewCurrentPrice(current[i]);         //update the option class with new current price 
		tmp_option.NewTime(expire-i*delta_t);           //new time to expiration
		opt.push_back(tmp_option);                      //add the new option class to the vector
	}
	return opt;
}
