#ifndef __JEEKJEEK_H__
#define __JEEKJEEK_H__

#include <vector>
#include <map>
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
	void login(std::string username, std::string password, std::string sessionId);
	void logout(std::string sessionId);
	void addJeek(std::string text, std::vector< std::string > inHashtags, std::vector< std::string > inMentions, std::string sessionId);
	void rejeek(std::string sessionId, std::string jeekId);
	void like(std::string sessionId, std::string jeekId);
	void dislike(std::string sessionId, std::string jeekId);
	bool hasLiked(std::string sessionId, std::string jeekId);

	Jeek* getJeek(std::string jeekId);
	std::vector<Jeek*> getUserJeeks(std::string sessionId);
	std::vector<Jeek*> getUserJeeksByUsername(std::string username);
	std::vector<Jeek*> getHashtagJeeks(std::string hashtag);

private:
	int findUserIndex(std::string username);
	int findHashtagIndex(std::string hashtag);
	
	IdMaker* idMaker;
	std::vector<User*> users;
	std::vector<Hashtag*> hashtags;
	std::map<std::string, User*> onlineUsers;
};

#endif