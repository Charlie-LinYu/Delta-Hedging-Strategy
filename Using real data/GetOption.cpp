#include "GetOption.h"
#include <iostream>
//#include <new>
//using namespace std;

std::map<std::string, Option*> GetOption(Option *tmp_opt, double strike, std::map<std::string, 
	double>& stock, double time, std::map<std::string, double>& interest, 
	double ini_vol, double d, std::map<std::string, double>& opt_price, bool c)
{
	std::map<std::string, Option*> date_option;            //declare the map for output
	string date;
	int index = 0;

	//loop through every element of the map of option market prices
	for (std::map<std::string, double>::iterator itr = opt_price.begin(); itr != opt_price.end(); itr++)
	{
		date = itr->first;         //get the date for the current loop

		//update the existed option class with new stock price, market price of the option,
		//risk free rate and other parameters
		tmp_opt[index].Update(strike, stock[date], time - index / 252.0, interest[date]/100.0, ini_vol, d, opt_price[date], c);
		
		//insert the pair of the date and the pointer to the above option object to the map
		date_option.insert(std::make_pair(date,&(tmp_opt[index])));
		index = index + 1;
	}
	return date_option;
}
