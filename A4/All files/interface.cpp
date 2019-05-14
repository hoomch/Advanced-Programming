#include "interface.hpp"
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