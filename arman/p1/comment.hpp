#ifndef __COMMENT_H__
#define	__COMMENT_H__

#include <string>
#include "message.hpp"

class User;

class Comment : public Message
{
public:
	Comment(User *_user, std::string _text, std::string _id) : Message(_user, _text, _id) {}
};

#endif

