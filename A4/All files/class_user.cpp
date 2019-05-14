#include "class_user.hpp"
int is_first_bigger(Date first , Date second){
	if (first.get_days() > second.get_days()) return 1;
	else if (first.get_days() == second.get_days()) return 0;
	else return -1;
}
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