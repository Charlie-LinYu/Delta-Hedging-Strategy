#include <random>
#include <iostream>
#include <vector>
#include <math.h>
#include "Option.h"
#include <numeric>
#include "Gen_Stock.h"
#include "Gen_Option.h"
#include "Hedging.h"
using namespace std;

int main()

{
	vector<double> stock_price;
	vector<Option> options;
	vector<double> CHE_dist;
	double s0 = 100, t = 0.4, mu = 0.05, sigma = 0.24, r = 0.025, strike = 105, expire = 0.4,q=0;
	bool call = true;
	int n = 100;
	double delta_t = t / (double)n;      //get the unit time period
	double seed = 1;                     //set seed
	string file_name = "result_for_task1.csv";
	stock_price = Gen_Stock(seed, n, s0, delta_t, mu, sigma);
	options = Gen_Option(strike, stock_price, expire, delta_t, r, sigma, q, call);
	Hedging hedge(stock_price, options, r, delta_t);
	hedge.print_out(file_name);

	std::mt19937 gen(seed);                       //set seed for 100 pathes
	std::normal_distribution<> dist(0, 1);        

	//repeat the above process 100 times and calculate the average cumulative hedging error
	for (int i = 1; i <= 100; i++)                
	{
		double z = dist(gen);
		stock_price = Gen_Stock(z, n, s0, delta_t, mu, sigma);
		options = Gen_Option(strike, stock_price, expire, delta_t, r, sigma, q, call);
		hedge.update(stock_price, options, r, delta_t);
		CHE_dist.push_back(hedge.get_CHE());
	}
	double sum = accumulate(CHE_dist.begin(), CHE_dist.end(), 0.0);
	double average_CHE = sum / CHE_dist.size();
	cout << "the average cumulative hedging error is: " << average_CHE << endl;
	cout << "the average cumulative hedging error (discounted) is: " << average_CHE*exp(-r*t) << endl;

	system("pause");
}