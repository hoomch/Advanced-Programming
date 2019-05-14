#ifndef __EXPERIENCE_H__
#define __EXPERIENCE_H__

#include "libraries.hpp"
#include "class_date.hpp"
using namespace std;
class Experience{
private:
	string companyName;
	string jobTitle;
	Date startsAt;
	Date endsAt;
public:
	Experience(string companyName , string jobTitle , string startsAt , string endsAt);
	string get_start();
	string get_end();
	string get_job();
	string get_company_name();
	Date get_startAt();
	Date get_endAt();
};

#endif