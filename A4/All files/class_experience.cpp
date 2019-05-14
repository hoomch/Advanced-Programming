#include "class_experience.hpp"
Experience::Experience(string companyName , string jobTitle , string startsAt , string endsAt){
	this->companyName=companyName;
	this->jobTitle=jobTitle;
	this->startsAt.convert_string_to_date(startsAt);
	this->endsAt.convert_string_to_date(endsAt);
}
string Experience::get_start(){
	string time = startsAt.get_string_date();
	if (time == NOW) return "NOW";
	else return time;
}
string Experience::get_end(){
	string time = endsAt.get_string_date();
	if (time == NOW) return "NOW";
	else return time;
}
string Experience::get_job(){
	return jobTitle;
}
string Experience::get_company_name(){
	return companyName;
}
Date Experience::get_startAt(){
	return startsAt;
}
Date Experience::get_endAt(){
	return endsAt;
}