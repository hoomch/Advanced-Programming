#include "user.hpp"
using namespace std;

User::User(string _username, string _displayname, string _password)
{
	username = _username;
	displayname = _displayname;
	password = _password;
}

bool User::isPasswordCorrect(std::string _password)
{
	return password == _password;
}

void User::addJeek(Jeek* newJeek)
{
	jeeks.push_back(newJeek);
}

Jeek* User::getJeek(std::string jeekId)
{
	for(int i = 0; i < jeeks.size(); i++)
	{
		if(jeeks[i]->getId() == jeekId)
			return jeeks[i];
	}
	return NULL;
}