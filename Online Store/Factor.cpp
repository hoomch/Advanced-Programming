#include "Factor.hpp"

using namespace std;

Factor::Factor(int _number, int _sum, string _first, string _last, string _id, string _phone ,vector<vector<string> > _index)
{
	fact_number = _number;
	first_name = _first;
	last_name = _last;
	user_name = _id;
	phone = _phone;
	factor_directory = _index;
	sum = _sum;
}

int Factor::cal_total_sum(vector <int> sum_directory)
{
	int total = 0;
	for (int j=0; j<sum_directory.size(); j++)
	{
		total += sum_directory[j];
	}
	total *= 105/100;
	return total;
}

void Factor::print_all()
{
	double sums_total = 0;
	cout << first_name << " " << last_name << " " << user_name << " " << phone << endl;
	cout << "#. Goods Name | Goods Count | Goods Price | Seller Username | Sum (count * price )" << endl;
	for (int i=0; i<factor_directory.size(); i++)
	{
		cout << i+1 << "." << factor_directory[i][0] << " | " << factor_directory[i][1] << " | " <<
				factor_directory[i][2] << " | " << factor_directory[i][3] << " | " << factor_directory[i][4] << endl;
		sums_total += stoi(factor_directory[i][4]);
	}
	cout << "Goods Sum = " << sums_total << endl;
	sums_total =  sums_total * 105/100;
	sum = sums_total;
	cout << "Total Sum = " << sums_total << endl;
}