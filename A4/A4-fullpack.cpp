#include <iostream>
#include <cstdlib>
#include <vector> 
#include <fstream>
#include <string>
#include <map>
#include <cmath>  
#include <iomanip>
#define NOW "INDIFINITE_DATE"
#define DATE "0123456789/"
#define SIZE 11
#define INVALID -1
#define TIMENOW 10000000
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
///////////////////////
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
/////////////////////
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
//////////////////
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
User::User(string firstName,string lastName,string emailAddress,string biography){
	this->firstName=firstName;
	this->lastName=lastName;
	this->emailAddress=emailAddress;
	this->biography=biography;
}
string User::get_id(){
	return emailAddress;
}
string User::get_firstName(){
	return firstName;
}
string User::get_lastName(){
	return lastName;
}
void User::add_new_exp(string companyName , string jobTitle , string startsAt , string endsAt){
	bool is_added=0;
	if (experiences.size() == 0) experiences.push_back(Experience(companyName , jobTitle , startsAt , endsAt));	
	else{
		Date start , end;
		start.convert_string_to_date(startsAt);
		end.convert_string_to_date(endsAt);
		for (int i = 0;i < experiences.size();i++){
			Date this_start , this_end;
			this_start=experiences[i].get_startAt();
			this_end=experiences[i].get_endAt();
			if (is_first_bigger(this_start , start) == 1){
				experiences.insert(experiences.begin()+i , (Experience(companyName , jobTitle , startsAt , endsAt)) );
				is_added=1;
				break;
			}	
			else if (is_first_bigger(this_start , start) == 0){
				if (is_first_bigger(this_end , end) == 1){
					experiences.insert(experiences.begin()+i , (Experience(companyName , jobTitle , startsAt , endsAt)));
					is_added=1;
					break;
				}
			}	
		}
		if (is_added == 0) experiences.push_back(Experience(companyName , jobTitle , startsAt , endsAt));	
	}
}
void User::add_skill(string skillName){
	skills.push_back(Skill(skillName));
}
bool User::is_skill_valid(string skillName){
	bool is_valid = false;
	for (int i=0;i<skills.size();i++)
		if (skills[i].get_skillName() == skillName) is_valid = true;
	return is_valid;
}
int User::find_skill_on_name(string skillName){
	int id = INVALID;
	for (int i = 0;i < skills.size();i++){
		if (skills[i].get_skillName() == skillName){
			id = i;
			break;
		}
	}
	return id;
}
float User::get_rate(string skillName){
	int id = find_skill_on_name(skillName);
	if (id != INVALID)
		return skills[id].getRate();
	else return 0;
}
void User::add_endorser_and_set_rate(string endorser , string skillName , float skillRate){
	int skill_id=find_skill_on_name(skillName);
	if (skill_id != INVALID){
		skills[skill_id].add_endorser(endorser , skillRate);
		skills[skill_id].calculate_rate();
	}
}
bool User::not_repeated_follower(User *follower){
	bool not_repeated=1;
	for (int i = 0;i < followers.size();i++)
		if (followers[i]->get_id() == follower->get_id()){
			not_repeated=0;
			break;
		}
	return not_repeated;	
}
void User::add_follower(User *follower){
	if (not_repeated_follower(follower))
		followers.push_back(follower);
}
void User::print_info(){
	cout << "Name: " << firstName << " " << lastName << endl;
	cout << "Email: " << emailAddress << endl;
	cout << "Biography: " << biography<< endl;
	cout << "Network: " << followers.size() << " connections" << endl;
	cout << "Experiences: " << endl;
	for (int i=0;i<experiences.size();i++)
		cout << "\t" << i+1 << ". " << experiences[i].get_start() << " - " << experiences[i].get_end() << " " <<  experiences[i].get_job() << " at " << experiences[i].get_company_name() <<  endl; 
	cout << "Skills: " << endl;
	for (int i=0;i<skills.size();i++)
		cout << "\t" << i+1 << ". " << skills[i].get_skillName() << " - " << skills[i].get_rate_with_precision() << endl;
}
//////////////////
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
Job::Job(User* userId ,string  jobTitle ,string startsAt ,string endsAt){
	this->userId = userId;
	this->jobTitle = jobTitle;
	this->startsAt.convert_string_to_date(startsAt);
	this->endsAt.convert_string_to_date(endsAt); 
}
string Job::get_start(){
	string time = startsAt.get_string_date();
	if (time == NOW) return "NOW";
	else return time;
}
string Job::get_end(){
	string time = endsAt.get_string_date();
	if (time == NOW) return "NOW";
	else return time;
}
string Job::get_jobTilte(){
	return jobTitle;
}
string Job::get_user_firstName(){
	return userId->get_firstName();
}
string Job::get_user_lastName(){
	return userId->get_lastName();
}
Date Job::get_startAt(){
	return startsAt;
}
Date Job::get_endAt(){
	return endsAt;
}
////////////////////
class Request{
private:
	string title;
	map<string,float> conditions;
public:
	Request(string title , map<string,float> conditions);
	map<string,float> get_conditions();
	string get_title();
};
Request::Request(string title , map<string,float> conditions){
	this->title=title;
	this->conditions=conditions;
}
map<string,float> Request::get_conditions(){
	return conditions;
}
string Request::get_title(){
	return title;
}
/////////////////////////
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
Company::Company(string name , string address , string description){
	this->name=name;
	this->address=address;
	this->description=description;
}
string Company::get_name(){
	return name;
}
void Company::add_new_request(string title , map<string,float> conditions){
	requests.push_back(Request(title , conditions));
	map<string,float>::iterator it = conditions.begin();
}
int Company::find_request_on_name(string jobTitle){
	int request_id = INVALID;
	for (int i=0;i<requests.size();i++){
		if (requests[i].get_title() == jobTitle){
			request_id = i;
			break;
		}
	}
	return request_id;
}
vector < Request > Company::get_requests(){
	return requests;
}
map<string,float> Company::get_condition_on_request(int request_id){
	return requests[request_id].get_conditions();
}
void Company::add_applicant(User* user , string jobTitle){
	applicants[user] = jobTitle;
	map <User*,string>::iterator it = applicants.begin();
}
void Company::add_job(User* best_applicant ,string jobTitle ,string startAt , string endsAt){
	bool is_title_repetitive=0;
	for (int i = 0;i < jobs.size();i++) 
		if (jobTitle == jobs[i].get_jobTilte()){
			is_title_repetitive = 1;
			break;
		}
	if (is_title_repetitive == 0){	
		bool is_added=0;
		if (jobs.size() == 0) jobs.push_back(Job(best_applicant , jobTitle , startAt , endsAt));	
		else{
			Date start , end;
			start.convert_string_to_date(startAt);
			end.convert_string_to_date(endsAt);
			for (int i = 0;i < jobs.size();i++){
				Date this_start , this_end;
				this_start=jobs[i].get_startAt();
				this_end=jobs[i].get_endAt();
				if (is_first_bigger(this_start , start) == 1){
					jobs.insert(jobs.begin()+i , (Job(best_applicant , jobTitle , startAt , endsAt)) );
					is_added=1;
					break;
				}	
				else if (is_first_bigger(this_start , start) == 0){
					if (is_first_bigger(this_end , end) == 1){
						jobs.insert(jobs.begin()+i , (Job(best_applicant , jobTitle , startAt , endsAt)));
						is_added=1;
						break;
					}
				}	
			}
			if (is_added == 0) jobs.push_back(Job(best_applicant , jobTitle , startAt , endsAt));
		}
	}
}
void Company::find_best_applicant_and_hire(string jobTitle , string startAt){
	User* best_applicant = NULL;
	float best_rate=0;
	int request_id = find_request_on_name(jobTitle);
	map<string,float> job_conditions = requests[request_id].get_conditions(); 
	map<string,float>::iterator job_condition_iterator = job_conditions.begin();
	map <User* , string >::iterator applicant_it = applicants.begin();
	//cout << applicants.size()<< endl;
	for (int i=0;i<applicants.size();i++ , (*applicant_it++)){
		if (applicant_it->second == jobTitle){
			float rate=0;
			for (int j=0;j<job_conditions.size();j++ , (*job_condition_iterator++)){
				rate += applicant_it->first->get_rate(job_condition_iterator->first);
			}
			if (rate > best_rate){
				best_applicant = applicant_it->first;
			}
		}
	}
	if (best_applicant != NULL){
		add_job(best_applicant , jobTitle , startAt , NOW);
		requests.erase(requests.begin() + request_id);
		best_applicant->add_new_exp(name , jobTitle , startAt , NOW);
	}
}
void Company::print_info(){
	cout << "Name: " << name << endl;
	cout << "Address: " << address << endl;
	cout << "Description: " << description << endl;
	cout << "Jobs: " << endl;
	for (int i=0;i<jobs.size();i++)
		cout << "\t" << i+1 << ". " << jobs[i].get_start() << " - " << jobs[i].get_end() << " " <<  jobs[i].get_jobTilte() << " by " << jobs[i].get_user_firstName() << " " << jobs[i].get_user_lastName() << endl; 
	cout << "Requests: " << endl;
	for (int i = 0;i < requests.size();i++){
		cout << i+1 << ". " << requests[i].get_title() << " - needed skills : " ;
		map<string,float> conditions = requests[i].get_conditions();
		map<string,float>:: iterator it = conditions.begin();
		for (int j=0;j<conditions.size();j++ , (*it++))	cout << "\t" << it->first << "(" << it->second << ") , ";
		cout << endl;
	}
	
}
////////////////////////
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
void LinkedIn::add_user(string firstName, string lastName, string emailAddress, string biography){
	bool is_name_repetitive=0;
	for (int i = 0;i < users.size();i++) 
		if (emailAddress == users[i].get_id()){
			is_name_repetitive = 1;
			break;
		}
	if (is_name_repetitive == 0)	
		users.push_back(User(firstName , lastName , emailAddress , biography));
}
void LinkedIn::add_company(string name , string address , string description){
	bool is_name_repetitive=0;
	for (int i = 0;i < companies.size();i++) 
		if (name == companies[i].get_name()){
			is_name_repetitive = 1;
			break;
		}
	if (is_name_repetitive == 0)	
	companies.push_back(Company(name , address , description));
}
int LinkedIn::find_user_on_id(string userId){
	int valid_id = INVALID;
	for (int i = 0 ; i < users.size() ; i++){
		if (users[i].get_id() == userId) valid_id=i;  
	}
	return valid_id;
}
int LinkedIn::find_company_on_id(string companyName){
	int valid_id = INVALID;
	for (int i = 0 ; i < companies.size() ; i++){
		if (companies[i].get_name() == companyName) valid_id=i;  
	}
	return valid_id;
}
void LinkedIn::add_experience(string userId, string companyId, string title, string startAt , string endsAt){
	int id = find_user_on_id(userId);
	int company_id = find_company_on_id(companyId);
	if (id != INVALID)
		users[id].add_new_exp(companyId , title , startAt , endsAt);
		companies[company_id].add_job(&users[id] , title ,  startAt , endsAt);
}
void LinkedIn::add_jobRequest(string companyName, string title, map<string, float> conditions){
	int id = find_company_on_id(companyName);
	if (id != INVALID)
		companies[id].add_new_request(title , conditions);
}
void LinkedIn::assign_skill(string userId , string skillName){
	int id = find_user_on_id(userId);
	if (id !=INVALID)
		users[id].add_skill(skillName);
}
void LinkedIn::endorse_skill(string endorserUserId , string skilledUserId , string skillName){
	int endorser_id = find_user_on_id(endorserUserId) , skilled_id = find_user_on_id(skilledUserId);
	if (endorser_id != INVALID && skilled_id != INVALID){
		if (users[skilled_id].is_skill_valid(skillName)){
			float endorser_rate;
			if(users[endorser_id].is_skill_valid(skillName))	endorser_rate=users[endorser_id].get_rate(skillName);
			else endorser_rate=0;
			users[skilled_id].add_endorser_and_set_rate(users[endorser_id].get_id() , skillName , endorser_rate);
		}
	}
}
void LinkedIn::following(string followerId , string followingId){
	int follower_id = find_user_on_id(followerId) , following_id = find_user_on_id(followingId);
	if (follower_id != INVALID && following_id != INVALID){
		users[follower_id].add_follower(&users[following_id]);
		users[following_id].add_follower(&users[follower_id]);
	}
}
bool LinkedIn::apply_for_job(string userId, string companyId, string jobTitle , bool suggest_or_apply){
	int valid_conditions=0;
	int user_id = find_user_on_id(userId) , company_id = find_company_on_id (companyId);
	if (user_id != INVALID && company_id != INVALID){
		int request_id = companies[company_id].find_request_on_name(jobTitle);
		if (request_id != INVALID){
			map <string,float> terms = companies[company_id].get_condition_on_request(request_id);
			map <string,float>:: iterator term_it = terms.begin();
			for (int i=0;i<terms.size();i++,(*term_it++)){
				string skill = term_it->first;
				float rate = term_it->second;
				int skill_id = users[user_id].find_skill_on_name(skill);
				if (skill_id != INVALID){
					if (rate <= users[user_id].get_rate(skill)) valid_conditions++;
				}	
			}
			if (valid_conditions == terms.size() && suggest_or_apply == 1){
				companies[company_id].add_applicant(&users[user_id] , jobTitle);
				return 1;
			}
			else if (valid_conditions == terms.size() && suggest_or_apply == 0){
				return 1;
			}
			else return 0;
		}
	}
}
void LinkedIn::hire_best_applicant(string companyId, string jobTitle, string startAt){
	int company_id = find_company_on_id(companyId);
	if (company_id != INVALID){
		int request_id = companies[company_id].find_request_on_name(jobTitle);
		if (request_id != INVALID){
			companies[company_id].find_best_applicant_and_hire(jobTitle , startAt);
		}
	}
}
void LinkedIn::print_user_profile(string userId){
	int id = find_user_on_id (userId);
	users[id].print_info();
}
void LinkedIn::print_company_profile(string companyName){
	int id = find_company_on_id(companyName);
	if (id != INVALID)	companies[id].print_info();
}
void LinkedIn::pre_print_suggested_job(string userId){
	int counter = 0;
	for (int i = 0;i < companies.size();i++){
		vector <Request> requests = companies[i].get_requests();
		for (int j = 0;j<requests.size();j++){
			if (apply_for_job(userId , companies[i].get_name() , requests[j].get_title() , 0)){
				counter ++;
				print_suggested_job(companies[i].get_name() , requests[j]  , counter) ;
			}
		}
	}
}
void LinkedIn::print_suggested_job(string companyId , Request suggested_request , int counter){
	cout << counter << ". " << suggested_request.get_title() << " in " << companyId << " - " << "needed skills : ";
	map<string,float> conditions = suggested_request.get_conditions();
	map<string,float>:: iterator it = conditions.begin();
	for (int j=0;j<conditions.size();j++ , (*it++))	cout << it->first << "(" << it->second << ") , ";
	cout << endl;
}
void LinkedIn::print_suggested_users(string companyName, string jobTitle){
	int valid_conditions = 0;
	int counter = 0;
	int request_id = INVALID;
	int company_id = find_company_on_id (companyName);
	if (company_id != INVALID)
		request_id = companies[company_id].find_request_on_name(jobTitle);
	if (request_id != INVALID){
		map<string,float> conditions = companies[company_id].get_condition_on_request(request_id);
		for (int i = 0;i < users.size();i++){
			valid_conditions = 0;
			map<string,float>:: iterator it = conditions.begin();
			for (int j = 0;j < conditions.size() ; j++ , (*it++)){
				string skill = it->first;
				float rate = it->second;
				int skill_id = users[i].find_skill_on_name(skill);
				if (skill_id != INVALID){
					if (rate <= users[i].get_rate(skill)) valid_conditions++;	
				}
			}
			if (valid_conditions == conditions.size()){
				counter++;
				cout << counter << " ." << endl;
				print_user_profile(users[i].get_id());
			}
		}
	}
}
///////////////////
class Interface
{
private:
    LinkedIn linkedin;
public:
    Interface();
    void addUser(string firstName, string lastName, string emailAddress, string biography);
    void addCompany(string name, string address, string description);
    void addExperience(string userId, string companyId, string title, string startAt , string endsAt);
    void addJobRequest(string companyName, string title, map<string, float> conditions);
    void assignSkill(string userId, string skillName);
    void endorseSkill(string endorserUserId, string skilledUserId, string skillName);
    void follow(string followerId, string followingId);
    void applyForJob(string userId, string companyId, string jobTitle);
    void hireBestApplicant(string companyId, string jobTitle, string startsAt);
    void printUserProfile(string userId);
    void printCompanyProfile(string companyName);
    void printSuggestedJobs(string userId);
    void printSuggestedUsers(string companyName, string jobTitle);
    void printNetwork(string userId, int level);

};
Interface::Interface(){

}
void Interface::addUser(string firstName, string lastName, string emailAddress, string biography){
	linkedin.add_user(firstName , lastName , emailAddress , biography);
}
void Interface::addCompany(string name, string address, string description){
	linkedin.add_company(name , address , description);
}
void Interface::addExperience(string userId, string companyId, string title, string startAt , string endsAt = NOW){
	linkedin.add_experience(userId , companyId , title , startAt , endsAt);
}
void Interface::addJobRequest(string companyName, string title, map<string, float> conditions){
	linkedin.add_jobRequest(companyName , title , conditions);
}
void Interface::assignSkill(string userId , string skillName){
	linkedin.assign_skill(userId , skillName);
}
void Interface::endorseSkill(string endorserUserId , string skilledUserId , string skillName){
	linkedin.endorse_skill(endorserUserId , skilledUserId , skillName);
}
void Interface::follow(string followerId, string followingId){
	linkedin.following(followerId , followingId);
}
void Interface::applyForJob(string userId, string companyId, string jobTitle){
	linkedin.apply_for_job(userId , companyId , jobTitle , 1);
}
void Interface::hireBestApplicant(string companyId, string jobTitle, string startsAt){
	linkedin.hire_best_applicant(companyId , jobTitle , startsAt);
}
void Interface::printUserProfile(string userId){
	linkedin.print_user_profile(userId);
}
void Interface::printCompanyProfile(string companyName){
	linkedin.print_company_profile(companyName);
}
void Interface::printSuggestedJobs(string userId){
	linkedin.pre_print_suggested_job(userId);
}
void Interface::printSuggestedUsers(string companyName, string jobTitle){
	linkedin.print_suggested_users(companyName , jobTitle);
}
///////////////////
int main()
{
	 Interface interface;

    interface.addUser("Haruki", "Murakami", "h.murakami@gmail.com", "I dream. Sometimes I think that’s the only right thing to do.");
    interface.addUser("J.K.", "Rowling", "jkr@hotmail.com", "It is our choices that show what we truly are, far more than our abilities.");
    interface.addUser("John", "Green", "john_green@yahoo.com", "If you don’t imagine, nothing ever happens at all.");
    interface.addUser("Dan", "Brown", "dan.brown@gmail.com", "Everything is possible. The impossible just takes longer.");
    interface.addUser("Rene", "Descartes", "rdc@ymail.com", "I think, therefore I am.");

    interface.addCompany("University of Tehran", "Enghelab Square, Tehran", "The best university ever.");
    interface.addCompany("Ofoq Publications", "12 Farvardin Street, Enghelab Square, Tehran", "Ofoq Publishers was founded in 1990 by Reza Hasheminejad");

    interface.addExperience("jkr@hotmail.com", "University of Tehran", "Student", "1/7/1380", "1/4/1395");
    interface.addExperience("jkr@hotmail.com", "University of Tehran", "Professor", "1/7/1395");
    interface.addExperience("dan.brown@gmail.com", "Ofoq Publications", "Author", "1/4/1394", "30/3/1395");
    interface.addExperience("dan.brown@gmail.com", "University of Tehran", "Researcher", "1/4/1395", "1/4/1396");

    interface.assignSkill("jkr@hotmail.com", "Writing");
    interface.assignSkill("jkr@hotmail.com", "Storytelling");
    interface.assignSkill("jkr@hotmail.com", "Editing");
    interface.assignSkill("jkr@hotmail.com", "Proofreading");
    interface.assignSkill("dan.brown@gmail.com", "Writing");
    interface.assignSkill("dan.brown@gmail.com", "Storytelling");
    interface.assignSkill("john_green@yahoo.com", "Writing");
    interface.assignSkill("rdc@ymail.com", "Writing");

    interface.endorseSkill("h.murakami@gmail.com", "jkr@hotmail.com", "Writing");
    interface.endorseSkill("h.murakami@gmail.com", "dan.brown@gmail.com", "Storytelling");

    interface.follow("jkr@hotmail.com", "dan.brown@gmail.com");
    interface.follow("jkr@hotmail.com", "john_green@yahoo.com");

    interface.printUserProfile("jkr@hotmail.com");
    interface.printCompanyProfile("University of Tehran");
}