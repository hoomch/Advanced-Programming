#ifndef __JOB_H__
#define __JOB_H__

#include "libraries.hpp"
#include "class_user.hpp"
#include "class_date.hpp"
using namespace std;
class Job{
private:
	User* userId;
	string jobTitle;
	Date startsAt;
	Date endsAt;
public:
	Job(User* userId ,string  jobTitle ,string startsAt ,string endsAt);
	string get_start();
	string get_end();
	string get_jobTilte();
	string get_user_firstName();
	string get_user_lastName();
	Date get_startAt();
	Date get_endAt();
};

#endif