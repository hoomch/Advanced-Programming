#include "class_date.hpp"
Date::Date(){
	year=0;
	month=1;
	day=1;
}
int Date::get_days(){
	if (is_now == 1) return TIMENOW;
	else return (year * 365 + month *30 + day);
}
bool Date::valid_char(char input){
	bool is_valid=0;
	for (int i=0;i<SIZE;i++)
		if (input == DATE[i]){
			is_valid=1;
			break;
		}
	return is_valid;
}
bool Date::check_valid_date(string date){ 
	int counter=0,slashes=0;
	for (int i=0;i<date.size();i++){
		if (valid_char(date[i])) counter++;
		if (date[i]== '/' && i!=0 && i!=date.size()-1) slashes++;
	}
	if (counter == date.size() && slashes==2) return 1;
	else return 0;
}
int Date::string_to_int(string input){
	int out_put=0;
	for (int i = 0 ; i < input.size() ; i++){
		out_put = out_put * 10;
		out_put += input[i] - '0';
	}
	return out_put;
}
void Date::convert_string_to_date(string date){
	if (date == NOW ) is_now=1;
	else{
		string year,month,day;
		int slashes=0;
		if (check_valid_date(date)){
			for (int i=0;i<date.size();i++){
				if (date[i]=='/') slashes++;
				else{
					if (slashes==2) year += date[i];
					if (slashes==1) month += date[i];
					if (slashes==0) day+= date[i];
				}
			}
		}
		this->year = string_to_int(year);
		this->month = string_to_int(month);
		this->day = string_to_int(day);
	}
}
string Date::int_to_string(int input){
	int temp = input;
	int zero = int('0');
	string out_put , out_put2;
	while (temp>0){
		out_put += char(zero + temp%10);
		temp = temp/10;
	}
	for (int i=out_put.size()-1;i>=0;i--)	out_put2 += out_put[i];
	return out_put2; 
}
string Date::get_string_date(){
	if (is_now == 1) return NOW;
	string date;
	date += int_to_string(day);
	date += '/';
	date += int_to_string(month);
	date += '/';
	date += int_to_string(year);
	return date;
}
int is_first_bigger(Date first , Date second){
	if (first.get_days() > second.get_days()) return 1;
	else if (first.get_days() == second.get_days()) return 0;
	else return -1;
}