#include "class_job.hpp"
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