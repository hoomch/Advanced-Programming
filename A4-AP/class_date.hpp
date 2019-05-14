#ifndef __DATE_H__
#define __DATE_H__

#include "libraries.hpp"
using namespace std;
class Date{
private:
	int year;
	int month;
	int day;
	bool is_now=0;
public:
	Date();
	int get_days();
	bool valid_char(char input);
	bool check_valid_date(string date);
	int string_to_int(string input);
	void convert_string_to_date(string date);
	void set_date(int year , int month , int day);
	string get_string_date();
	string int_to_string(int input);
};

#endif