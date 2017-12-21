#include "ReadCSV.h"
#include <fstream>

std::map<std::string, double> ReadCSV(const std::string & file_name)
{
	std::ifstream infile;
	std::string part1, part2;
	infile.open(file_name);
	std::map<std::string, double> date_price;
	while (infile.good())
	{
		std::getline(infile, part1, ',');
		std::getline(infile, part2);
		//judge whether the first part is a date
		if (part1.size() == 10 && part1.substr(4, 1) == "-" && part1.substr(7, 1) == "-")
		{
			double price = stod(part2);
			date_price.insert(std::pair<std::string, double>(part1, price));
		}
	}
	infile.close();
	return date_price;
}
