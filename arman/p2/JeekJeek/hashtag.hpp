#ifndef __HASHTAG_H__
#define __HASHTAG_H__

#include <string>
#include <vector>
#include "jeek.hpp"
#include <sstream>

class Hashtag
{
public:
	Hashtag(Jeek *jeek, std::string _title);
	void addJeek(Jeek *newJeek);
	std::string getTitle() { return title; }
	std::vector<Jeek*> getJeeks() { return jeeks; }
private:
	std::string title;
	std::vector<Jeek*> jeeks;
};

#endif