#include "class_company.hpp"
int is_first_bigger(Date first , Date second){
	if (first.get_days() > second.get_days()) return 1;
	else if (first.get_days() == second.get_days()) return 0;
	else return -1;
}
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