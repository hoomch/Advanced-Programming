#ifndef __INTERFACE_H__
#define	__INTERFACE_H__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "jeekJeek.hpp"
#include "user.hpp"
#include "exception.hpp"

class Interface
{
public:
	Interface();
	void start();
private:
	JeekJeek* jeekJeek;
	std::vector<std::string> getWords(std::stringstream &commandSS);
	void processCommand(std::string command);
	void processSignup(std::vector<std::string> words);
	void processLogin(std::vector<std::string> words);
	void processJeek();
	void processSearch(std::vector<std::string> words);
	bool processJeekCommand(std::string jeekCommand);
	void processComment(std::vector<std::string> words);
	void processReply(std::vector<std::string> words);
	void processRejeek(std::vector<std::string> words);
	void processShowJeek(std::vector<std::string> words);
	void processShowComment(std::vector<std::string> words);
	void processShowReply(std::vector<std::string> words);
	void processLike(std::vector<std::string> words);
	void processDislike(std::vector<std::string> words);
	void processFollow(std::vector<std::string> words);
	void processUnfollow(std::vector<std::string> words);
};

#endif