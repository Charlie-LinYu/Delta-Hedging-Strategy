#include "Hedging.h"
#include <string>
#include <vector>
#include <math.h>
#include <fstream>

Hedging::Hedging(std::map<std::string, Option*>& opt)
{
	int index = 0;

	//loop through every element in the map of option pointers
	for (std::map<std::string, Option*>::iterator itr = opt.begin(); itr != opt.end(); itr++)
	{
		date.push_back(itr->first);                             //get the date for current loop
		stocks.push_back((itr->second)->get_underlying());      //add current price to the stock vector
		qp.push_back((itr->second)->get_real_price());          //add market price of the option to the vector
		risk_free.push_back((itr->second)->get_risk_free());    //add current risk free rate to the vector
		implied_vol.push_back((itr->second)->get_implied_vol());//add implied volatility to the vector
		delta.push_back((itr->second)->delta());                //add delta to the vector
		if (index == 0)
		{
			B_new.push_back(qp[index]-delta[index]*stocks[index]);      //calculate B_0 for CHE
			B_old.push_back(qp[index] - delta[index] * stocks[index]);  //calcualte B_0 for HE
			HE.push_back(0);           //calcualte hedging error at time 0
			CHE.push_back(0);          //calculate cumulative hedging error at time 0
			PNL.push_back(0);          //profit and loss at time 0
		}
		else
		{
			//B_i for calculating cumulative hedging error
			B_new.push_back(delta[index-1]*stocks[index] + B_new[index-1]*exp(risk_free[index-1]/252.0) - delta[index] * stocks[index]);
			
			//B_i for calculating hedging error
			B_old.push_back(qp[index] - delta[index] * stocks[index]);

			//hedging error at time i
			HE.push_back(delta[index-1]*stocks[index] + B_old[index-1]*exp(risk_free[index-1]/252.0) -qp[index]);
			
			//cumulative hedging error till time i
			CHE.push_back(delta[index - 1] * stocks[index] + B_new[index - 1] * exp(risk_free[index - 1] / 252.0) - qp[index]);
			
			//profit and loss at time i
			PNL.push_back(qp[0] - qp[index]);
		}
		index = index + 1;
	}

}

void Hedging::print_out(const std::string & filename)
{
	std::ofstream outfile;
	outfile.open(filename, std::ios::out | std::ios::trunc);
	outfile << "date" << "," << "S" << "," << "V" << "," << "Implied Volatility" << "," << "Delta" << "," <<
		"Hedging Error" << "," << "Cumulative Hedging Error" << "," << "PNL" << std::endl;
	for (int i = 0; i < date.size();i++)
	{
		outfile << date[i] << "," << stocks[i] << "," << qp[i] << "," << implied_vol[i] << "," 
			<< delta[i] << "," << HE[i] << "," << CHE[i] << "," << PNL[i] << std::endl;
	}
	outfile.close();
}
