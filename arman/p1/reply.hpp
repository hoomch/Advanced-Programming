#ifndef __REPLY_H__
#define __REPLY_H__

#include <string>
#include "message.hpp"

class User;

class Reply : public Message
{
public:
	Reply(User* _user, std::string _text, std::string _id) : Message(_user, _text, _id) {}
};

#endif	