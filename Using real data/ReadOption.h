#ifndef ReadOption_H_INCLUDED
#define ReadOption_H_INCLUDED
#include <map>
#include <string>

/*
read the csv file of options,
apply filtrations to select required options,
return the map that matches the market price of options with the date
*/
std::map<std::string, double> ReadOption(const std::string & file_name, 
	std::string t0, std::string tn, std::string maturity, std::string strike, bool call);


#endif // ReadOption_H_INCLUDED
