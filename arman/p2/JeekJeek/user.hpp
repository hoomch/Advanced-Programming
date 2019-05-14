#ifndef __USER_H__
#define __USER_H__

#include "jeek.hpp"
#include <string>
#include <vector>
#include <sstream>

#define NOT_FOUND -1

class User
{
public:
	User(std::string _username, std::string _displayname, std::string _password);
	std::string getUsername() const { return username; }
	std::string getDisplayname() const { return displayname; }
	std::vector<Jeek*> getJeeks() { return jeeks; }
	bool isPasswordCorrect(std::string _password);
	void addJeek(Jeek* newJeek);
	Jeek* getJeek(std::string jeekId);
private:
	std::string username;
	std::string displayname;
	std::string password;

	std::vector<Jeek*> jeeks;
	std::vector<User*> followers;
	std::vector<User*> followings;
};

#endif