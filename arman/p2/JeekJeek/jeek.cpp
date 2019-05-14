#include "jeek.hpp"
#include "hashtag.hpp"
#include "user.hpp"
using namespace std;

void Jeek::addHashtag(Hashtag* hashtag)
{
	hashtags.push_back(hashtag);
}

void Jeek::addHashtags(vector<Hashtag*> inHashtags)
{
	for(int i = 0; i < inHashtags.size(); i++)
		hashtags.push_back(inHashtags[i]);
}

void Jeek::addMention(User* _user)
{
	mentionedUsers.push_back(_user);
}

void Jeek::addMentions(vector<User*> inMentions)
{
	for(int i = 0; i < inMentions.size(); i++)
		mentionedUsers.push_back(inMentions[i]);
}

string Jeek::getOwnerDisplayname() 
{ 
	return user->getDisplayname(); 
}

void Jeek::addLike(User* _user)
{
	int likerIndex = findLikerIndex(_user);

	if(likerIndex != NOT_FOUND)
		return;
	else
		likers.push_back(_user);
}

void Jeek::deleteLike(User* _user)
{
	int likerIndex = findLikerIndex(_user);

	if(likerIndex == NOT_FOUND)
		return;
	else
		likers.erase(likers.begin() + likerIndex);
}

int Jeek::findLikerIndex(User* _user) const
{
	for(int i = 0; i < likers.size(); i++)
	{
		if(likers[i]->getUsername() == _user->getUsername())
			return i;
	}
	return NOT_FOUND;
}

bool Jeek::hasLiker(User* user)
{
	for(int i = 0; i < likers.size(); i++)
	{
		if(user->getUsername() == likers[i]->getUsername())
			return true;
	}
	return false;
}