#include "hashtag.hpp"

Hashtag::Hashtag(Jeek *jeek, std::string _title)
{
	title = _title;
	jeeks.push_back(jeek);
}

void Hashtag::addJeek(Jeek *newJeek)
{
	jeeks.push_back(newJeek);
}

void Hashtag::printJeeks()
{
	for(int i = 0; i < jeeks.size(); i++)
		jeeks[i]->print();
}