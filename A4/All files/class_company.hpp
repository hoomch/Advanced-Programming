#ifndef __COMPANY_H__
#define __COMPANY_H__

#include "libraries.hpp"
#include "class_job.hpp"
#include "class_request.hpp"
#include "class_user.hpp"
using namespace std;
class Company{
private:
	string name;
	string address;
	string description;
	vector < Job > jobs;
	vector < Request > requests;
	map <User* , string > applicants;
public:
	Company(string name , string address , string description);
	string get_name();
	void add_new_request(string title , map<string,float> conditions);
	int find_request_on_name(string jobTitle);
	vector < Request > get_requests();
	map<string,float> get_condition_on_request(int request_id);
	void add_applicant(User* userId , string jobTitle);
	void add_job(User* userId ,string  jobTitle ,string startsAt ,string endsAt);
	void find_best_applicant_and_hire(string jobTitle , string startAt);
	void print_info();
};

#endif