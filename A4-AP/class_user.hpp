#ifndef __USER_H__
#define __USER_H__

#include "libraries.hpp"
#include "class_experience.hpp"
#include "class_skill.hpp"
using namespace std;
class User{
private:
	string firstName;
	string lastName;
	string emailAddress;
	string biography;
	vector <Experience> experiences;
	vector <Skill> skills;
	vector <User *> followers;
public:
	User(string firstName,string lastName,string emailAddress,string biography);
	string get_firstName();
	string get_lastName();
	string get_id();
	void add_new_exp(string companyName , string jobTitle , string startsAt , string endsAt);
	void add_skill(string skillName);
	bool is_skill_valid(string skillName);
	int find_skill_on_name(string skillName);
	float get_rate(string skillName);
	void add_endorser_and_set_rate(string firstName , string skillName , float skillRate);
	bool not_repeated_follower(User *follower);
	void add_follower(User *follower);
	void print_info();
};

#endif