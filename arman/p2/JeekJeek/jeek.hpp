#ifndef __JEEK_H__
#define __JEEK_H__

#include "message.hpp"
#include "exception.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define NOT_FOUND -1

class Hashtag;
class User;

class Jeek : public Message
{
public:
	Jeek(User* user, std::string text, std::string id) : Message(user, text, id), rejeeks(0) {}
	std::string getOwnerDisplayname();
	std::vector<Hashtag*> getHashtags() { return hashtags; }
	std::vector<User*> getMentionedUsers() { return mentionedUsers; }
	int getLikesNumber() { return likers.size(); }
	int getRejeeksNumber() { return rejeeks; }
	std::string getText() { return text; }
	
	void increaseRejeeks() { rejeeks++; }
	void addHashtag(Hashtag* hashtag);
	void addMention(User* _user);
	void addLike(User* _user);
	void deleteLike(User* _user);
	bool hasLiker(User* user);
	void addHashtags(std::vector<Hashtag*> inHashtags);
	void addMentions(std::vector<User*> inMentions);

private:
	int rejeeks;
	std::vector<User*> likers;
	std::vector<Hashtag*> hashtags;
	std::vector<User*> mentionedUsers;
	int findLikerIndex(User* _user) const;
};

#endif