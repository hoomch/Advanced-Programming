#ifndef __LINKEDIN_H__
#define __LINKEDIN_H__

#include "class_user.hpp"
#include "class_company.hpp"
using namespace std;
class LinkedIn{
private:
	vector < User > users;
	vector < Company > companies;
public:
	int find_user_on_id(string userId);
	int find_company_on_id(string companyName);
	void add_user(string firstName, string lastName, string emailAddress, string biography);
	void add_company(string name , string address , string description);
	void add_experience(string userId, string companyId, string title, string startAt , string endsAt);
	void add_jobRequest(string companyName, string title, map<string, float> conditions);
	void assign_skill(string userId , string skillName);
	void endorse_skill(string endorserUserId , string skilledUserId , string skillName);
	void following(string followerId , string followingId);
	bool apply_for_job(string userId, string companyId, string jobTitle , bool suggest_or_apply);
	void hire_best_applicant(string companyId, string jobTitle, string startAt);
	void print_user_profile(string userId);
	void print_company_profile(string companyName);
	void pre_print_suggested_job(string userId);
	void print_suggested_job(string companyId , Request suggested_request , int counter);
	void print_suggested_users(string companyName, string jobTitle);
};

#endif