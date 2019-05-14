#include "class_LinkedIn.hpp"
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