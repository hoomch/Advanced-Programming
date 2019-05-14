#ifndef __JEEKJEEK_H__
#define __JEEKJEEK_H__

#include <vector>
#include "user.hpp"
#include "hashtag.hpp"
#include "idMaker.hpp"

#define NOT_FOUND -1
#define TEXT_MAX_LENGTH 140

class JeekJeek
{
public:
	JeekJeek();
	void signup(std::string username, std::string displayname, std::string password);
	void login(std::string username, std::string password);
	void logout();
	void addJeek(std::string text, std::vector< std::string > inHashtags, std::vector< std::string > inMentions);
	void search(std::string keyword);
	void addComment(std::string jeekId, std::string text);
	void addReply(std::string id, std::string text);
	void rejeek(std::string jeekId);
	void showJeek(std::string jeekId);
	void showComment(std::string CommentId);
	void showReply(std::string replyId);
	void like(std::string jeekId);
	void dislike(std::string jeekId);
	void follow(std::string username);
	void unfollow(std::string username);
	void showNotifications();
private:
	int findUserIndex(std::string username);
	int findHashtagIndex(std::string hashtag);
	bool isUserLoggedIn();
	void printUser(std::string username);
	void printHashtag(std::string hashtag);
	Message* getMessage(std::string id);
	
	IdMaker* idMaker;
	User* currentUser;
	std::vector<User*> users;
	std::vector<Hashtag*> hashtags;
};

#endif