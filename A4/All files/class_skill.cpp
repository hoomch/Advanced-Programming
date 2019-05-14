#include "class_skill.hpp"
Skill::Skill(string skillName){
	this->skillName=skillName;
	skillRate=0;
}
string Skill::get_skillName(){
	return skillName;
}
bool Skill::no_repeated_endorser(string endorser){
	bool no_reapeat=1;
	map<string,float>:: iterator it = endorsers_rate.begin();
	for (int i=0;i<endorsers_rate.size();i++ , (*it++)){
		if (it->first == endorser){
			no_reapeat=0;
			break;
		}
	}
	return no_reapeat;
}
void Skill::add_endorser(string endorser , float rate){
	if (no_repeated_endorser(endorser))
		endorsers_rate[endorser] = rate;
}
float Skill::getRate(){
	return skillRate;
}
int Skill::power(int base , int pow){
	int answer=1;
	for (int i = 0;i < pow;i++)	answer *= base;
	return answer;
}
float Skill::get_rate_with_precision(){
	float rate = skillRate;
	int precision = find_precision(rate);
	rate = rate * power(10,precision);
	rate = (int) rate;
	rate = rate / power(10,precision);
	return rate;
}
int Skill::find_precision(float rate){
	if (rate - (int)rate == 0) return 0;
	else if (rate*10 - (int)(rate*10) == 0) return 1;
	else return 2;
}
void Skill::calculate_rate(){
	float sum_of_endorses=0;
	map<string,float>:: iterator it = endorsers_rate.begin();
	for (int i=0;i<endorsers_rate.size();i++ , (*it++))	sum_of_endorses += it->second;
	sum_of_endorses ++;
	sum_of_endorses = sqrt(sum_of_endorses);
	skillRate = sum_of_endorses;
}