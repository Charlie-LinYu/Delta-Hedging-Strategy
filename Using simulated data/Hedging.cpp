#include "Hedging.h"
#include <math.h>
#include <fstream>

Hedging::Hedging(std::vector<double> st, std::vector<Option> op, double r, double delta_t)
{
	stocks = st;
	options = op;

	B.push_back(options[0].BS() - options[0].delta() * stocks[0]);      //for t = 0
	CHE.push_back(0);                                                   //for t = 0
	double tmp_B, tmp_CHE;
	for (int i = 1; i < stocks.size(); i++)
	{
		//calculate the B_i
		tmp_B = options[i-1].delta() * stocks[i] + B[i - 1] * exp(r*delta_t) - options[i].delta() * stocks[i];
		B.push_back(tmp_B);
		//calculate the cumulative hedging error of time i
		tmp_CHE = options[i - 1].delta() * stocks[i] + B[i - 1] * exp(r*delta_t) - options[i].BS();
		CHE.push_back(tmp_CHE);
	}
}

void Hedging::update(std::vector<double> st, std::vector<Option> op, double r, double delta_t)
{
	stocks.clear();
	options.clear();
	B.clear();
	CHE.clear();

	//clear all member variables and repeat the constructor
	stocks = st;
	options = op;
	B.push_back(options[0].BS() - options[0].delta() * stocks[0]);
	CHE.push_back(0);
	double tmp_B, tmp_CHE;
	for (int i = 1; i < stocks.size(); i++)
	{
		tmp_B = options[i - 1].delta() * stocks[i] + B[i - 1] * exp(r*delta_t) - options[i].delta() * stocks[i];
		B.push_back(tmp_B);
		tmp_CHE = options[i - 1].delta() * stocks[i] + B[i - 1] * exp(r*delta_t) - options[i].BS();
		CHE.push_back(tmp_CHE);
	}
}

void Hedging::print_out(const std::string filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::trunc);
	outfile << "Index" << "," << "Stock_price" << "," << "BS_Price" << ","  << "Delta" << "," <<
		"Cumulative Hedging Error" << std::endl;
	for (int i = 0; i < stocks.size(); i++)
	{
		outfile << i << "," << stocks[i] << "," << options[i].BS() << "," << 
			options[i].delta() << "," << CHE[i] << std::endl;
	}
	outfile.close();
}

double Hedging::get_CHE()
{
	return CHE[CHE.size() - 1];
}
