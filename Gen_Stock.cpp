#include "Gen_Stock.h"
#include <random>
//#include <numeric>

std::vector<double> Gen_Stock(double seed, int times, double s0, double delta_t, double miu, double sigma)
{
	std::mt19937 gen(seed);
	std::normal_distribution<> dist(0, 1);
	std::vector<double> stock_price;
	double z, tmp_stock;
	for (int i = 0; i <= 100; i++)
	{
		if (i == 0)
		{
			stock_price.push_back(s0);
		}
		else
		{
			z = dist(gen);      //generate the random number
			//simulate a new stock price
			tmp_stock = stock_price[i - 1] + miu * stock_price[i - 1] * delta_t + sigma * stock_price[i - 1] * sqrt(delta_t) * z;
			stock_price.push_back(tmp_stock);
		}
	}
	return stock_price;

}
