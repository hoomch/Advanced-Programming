#ifndef FACTOR_H
#define FACTOR_H

#include <iostream>

#include <vector>

#include <string>

class Factor
{
	private:
		int fact_number,sum;
		std::string first_name, last_name, user_name, phone;
		std::vector<std::vector<std::string> > factor_directory;
	public:
		Factor(int _number, int _sum, std::string _first, std::string _last, std::string _id, std::string _phone,
			   std::vector<std::vector<std::string> > _index);
		void print_all();
		int get_number() {return fact_number;}
		int get_sum() {return sum;}
		int cal_total_sum(std::vector <int> sum_directory);
		std::string get_id() {return user_name;}
		std::string get_first_name() {return first_name;}
		std::string get_last_name() {return last_name;}
		std::string get_phone() {return phone;}
};

#endif