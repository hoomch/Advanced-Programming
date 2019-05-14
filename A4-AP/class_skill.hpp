#ifndef __SKILL_H__
#define __SKILL_H__

#include "libraries.hpp"
using namespace std;
class Skill{
private:
	map<string,float> endorsers_rate;
	string skillName;
	float skillRate;
public:
	Skill(string skillName);
	string get_skillName();
	float getRate();
	int power(int base , int pow);
	float get_rate_with_precision();
	bool no_repeated_endorser(string endorser);
	void add_endorser(string endorser , float rate);
	int find_precision(float rate);
	void calculate_rate();
};

#endif