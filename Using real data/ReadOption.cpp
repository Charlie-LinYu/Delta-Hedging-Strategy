#include "ReadOption.h"
#include <string>
#include <fstream>

//using namespace std;

std::map<std::string, double> ReadOption(const std::string & file_name, 
	std::string t0, std::string tn, std::string maturity, std::string strike, bool call)
{
	std::ifstream infile;
	std::string part[6];
	infile.open(file_name);
	std::map<std::string, double> option_price;
	std::string cp_flag;
	if (call) { cp_flag = "C"; }
	else { cp_flag = "P"; }

	while (infile.good())
	{
		for (int i = 0; i < 5; i++)
		{
			std::getline(infile, part[i], ',');
		}
		std::getline(infile, part[5]);

		//filter according to users' input
		if (part[0].size() == 10 && part[0].substr(4, 1) == "-" && part[0].substr(7, 1) == "-" && part[0] >= t0 &&
			part[0] <= tn && part[1] == maturity && part[2] == cp_flag && (part[3]) == strike)
		{
			double tmp_price = (std::stod(part[4]) + std::stod(part[5])) / 2;
			option_price.insert(std::pair<std::string, double>(part[0], tmp_price));
		}
	}
	infile.close();
	return option_price;
}
