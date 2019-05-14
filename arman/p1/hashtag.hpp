#ifndef __HASHTAG_H__
#define __HASHTAG_H__

#include <string>
#include <vector>
#include "jeek.hpp"

class Hashtag
{
public:
	Hashtag(Jeek *jeek, std::string _title);
	std::string getTitle() { return title; }
	void addJeek(Jeek *newJeek);
	void printJeeks();
private:
	std::string title;
	std::vector<Jeek*> jeeks;
};

#endif