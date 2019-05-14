#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "class_LinkedIn.hpp"
#include <string>
#include <map>

#define NOW "INDIFINITE_DATE"

class Interface
{
private:
    LinkedIn linkedin;
public:
    Interface();
    void addUser(std::string firstName, std::string lastName, std::string emailAddress, std::string biography);
    void addCompany(std::string name, std::string address, std::string description);
    void addExperience(std::string userId, std::string companyId, std::string title, std::string startAt , std::string endsAt );
    void addJobRequest(std::string companyName, std::string title, std::map<std::string, float> conditions);
    void assignSkill(std::string userId, std::string skillName);
    void endorseSkill(std::string endorserUserId, std::string skilledUserId, std::string skillName);
    void follow(std::string followerId, std::string followingId);
    void applyForJob(std::string userId, std::string companyId, std::string jobTitle);
    void hireBestApplicant(std::string companyId, std::string jobTitle, std::string startsAt);
    void printUserProfile(std::string userId);
    void printCompanyProfile(std::string companyName);
    void printSuggestedJobs(std::string userId);
    void printSuggestedUsers(std::string companyName, std::string jobTitle);
    void printNetwork(std::string userId, int level);
};

#endif