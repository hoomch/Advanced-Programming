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

void Jeek::print() const
{
	cout << id << ' ' << user->getDisplayname() << '\n';
	cout << text << '\n';
}

void Jeek::showJeek() const
{
	cout << user->getDisplayname() << '\n';
	cout << text << '\n';

	for(int i = 0; i < hashtags.size(); i++)
		cout << '#' << hashtags[i]->getTitle() << '\n'; 

	for(int i = 0; i < mentionedUsers.size(); i++)
		cout << '@' << mentionedUsers[i]->getUsername() << '\n';

	cout << "Likes " << likers.size() << '\n';
	cout << "Rejeeks " << rejeeks << '\n';
	cout << "Comments:\n";
	showCommentsId();
}

void Jeek::addLike(User* liker)
{
	int likerIndex = findLikerIndex(liker);

	if(likerIndex != NOT_FOUND)
	{
		throw Duplicate_Like_Exception();
	}
	else
	{
		likers.push_back(liker);
	}
}

void Jeek::deleteLike(User* disliker)
{
	int likerIndex = findLikerIndex(disliker);

	if(likerIndex == NOT_FOUND)
	{
		throw Not_Liked_Exception();
	}
	else
	{
		likers.erase(likers.begin() + likerIndex);
	}
}

int Jeek::findLikerIndex(User* liker) const
{
	for(int i = 0; i < likers.size(); i++)
	{
		if(likers[i]->getUsername() == liker->getUsername())
			return i;
	}
	return NOT_FOUND;
}