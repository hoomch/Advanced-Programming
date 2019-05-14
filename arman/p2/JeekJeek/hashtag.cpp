#include "hashtag.hpp"
using namespace std;

Hashtag::Hashtag(Jeek *jeek, std::string _title)
{
	title = _title;
	jeeks.push_back(jeek);
}

void Hashtag::addJeek(Jeek *newJeek)
{
	jeeks.push_back(newJeek);
}
