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
	virtual ~Message() = default;
	std::string getText() const { return text; }
	std::string getId() const { return id; }
	User* getOwner() { return user; }
	void addComment(Message* comment);
	void addReply(Message* reply);
	void showCommentsId() const;
	void showRepliesId() const;
	void showMessage() const;
protected:
	User* user;
	std::string id;
	std::string text;
	std::vector<Message*> comments;
	std::vector<Message*> replies;
};

#endif