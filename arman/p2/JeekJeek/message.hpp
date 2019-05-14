#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <iostream>
#include <string>
#include <vector>

class User;

class Message
{
public:
	Message(User* _user, std::string _text, std::string _id) : user(_user), text(_text), id(_id) {}
	std::string getText() const { return text; }
	std::string getId() const { return id; }

protected:
	User* user;
	std::string id;
	std::string text;
};

#endif