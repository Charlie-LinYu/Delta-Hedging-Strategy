#ifndef ReadCSV_H_INCLUDED
#define ReadCSV_H_INCLUDED

#include <map>
#include <string>

//read data from a csv file, which contains two columns,
//the first column is dates, the second column is prices
std::map<std::string, double> ReadCSV(const std::string& file_name);


#endif // ReadCSV_H_INCLUDED
