#ifndef __JEEK_H__
#define __JEEK_H__

#include <iostream>
#include <string>
#include <vector>
#include "message.hpp"
#include "exception.hpp"

#define NOT_FOUND -1

class Hashtag;
class User;

class Jeek : public Message
{
public:
	Jeek(User* _user, std::string _text, std::string _id) : Message(_user, _text, _id), rejeeks(0) {}
	std::vector<Hashtag*> getHashtags() { return hashtags; }
	std::vector<User*> getMentionedUsers() { return mentionedUsers; }
	void increaseRejeeks() { rejeeks++; }
	void addHashtag(Hashtag* hashtag);
	void addHashtags(std::vector<Hashtag*> inHashtags);
	void addMention(User* _user);
	void addMentions(std::vector<User*> inMentions);
	void addLike(User* liker);
	void deleteLike(User* disliker);
	void print() const;
	void showJeek() const;
private:
	int rejeeks;
	std::vector<User*> likers;
	std::vector<Hashtag*> hashtags;
	std::vector<User*> mentionedUsers;
	int findLikerIndex(User* liker) const;
};

#endif