#include <ql/quantlib.hpp>
#include <ql/time/calendar.hpp>
#include <ql/time/calendars/unitedstates.hpp>
#include <ql/time/calendars/weekendsonly.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "ReadCSV.h"
#include "ReadOption.h"
#include "Option.h"
#include "GetOption.h"
#include "Hedging.h"
//for use of quantlib, we should add the preprocessor definitions of
//_SCL_SECURE_NO_WARNINGS

using namespace std;

//for test only, output the information of an option class
ostream& operator<<(std::ostream& os, const Option& opt);

//judge if a string is a number
bool isnum(string s);

int main()
{
	string file_name1 = "interest.csv";
	string file_name2 = "sec_GOOG.csv";
	string file_name3 = "op_GOOG.csv";
	string file_name4 = "result_for_task2.csv";
	string t0, tn, maturity, strike, c;
	bool call;
	while (1)
	{
		cout << "Please input the start date(YYYY-MM-DD), end date(YYYY-MM-DD), "
			"expired date(YYYY-MM-DD), strike price(Positive integer) and the option type(C or P), "
			"(Please use space as the delimited sign):" << endl;
		cin >> t0 >> tn >> maturity >> strike >> c;
		//make a simple check, to make sure the input information is legal
		if (t0.size() == 10 && tn.size() == 10 && maturity.size() == 10 && isnum(strike) && (c == "C" || c == "P"))
		{
			
			break;
		}
		else
		{
			cout << "The format of your input is wrong, please input again." << endl;
		}
	}
	if (c == "C") { call = true; }
	else if(c =="P") { call = false; }

	//initialize a calendar class and the date class for the start date and the expiration data
	//to calculate the business days before expiration
	QuantLib::Calendar myCal = QuantLib::UnitedStates();
	QuantLib::Month m1 = (QuantLib::Month)stoi(t0.substr(5, 2));
	QuantLib::Month m2 = (QuantLib::Month)stoi(maturity.substr(5, 2));

	QuantLib::Date date1(stoi(t0.substr(8, 2)), m1, stoi(t0.substr(0,4)));
	QuantLib::Date date2(stoi(maturity.substr(8, 2)), m2, stoi(maturity.substr(0, 4)));

	double expired_t = myCal.businessDaysBetween(date1,date2) / 252.0;  
	
	double ini_volatility = 2;          //initial value for the binary search to get the implied volatility
	double d = 0;
	map<string, double> interest_rate;
	map<string, double> stock_prices;
	map<string, double> option_prices;
	map<string, Option*> options;
	interest_rate = ReadCSV(file_name1);
	stock_prices = ReadCSV(file_name2);
	
	option_prices = ReadOption(file_name3, t0, tn, maturity, strike, call);
	Option * tmp_opt = new Option[option_prices.size()];

	options = GetOption(tmp_opt, stoi(strike), stock_prices, expired_t, interest_rate, ini_volatility, d, option_prices, call);

	Hedging hedge(options);

	hedge.print_out(file_name4);

	delete[] tmp_opt;
	system("pause");
	return 0;
}

ostream& operator<<(ostream& os, const Option& opt)
{
	os << "strike: " << opt.k << "current: " << opt.s << "time: " << opt.t << "risk_free: " << opt.r << "sigam: " << opt.sigma << "qp: " << opt.real_p << "call: " << opt.call;
	return os;
}

bool isnum(string s)
{
	// code for judging whether a string is a number
	stringstream sin(s);
	double testnumber;
	char testchar;
	if (!(sin >> testnumber)) {
		return false;
	}
	if (sin >> testchar) {
		return false;
	}
	else {
		return true;
	}
}