#include "user.hpp"
using namespace std;

User::User(string _username, string _Displayname, string _password)
{
	username = _username;
	Displayname = _Displayname;
	password = _password;
}

bool User::isPasswordCorrect(std::string _password)
{
	return password == _password;
}

void User::addJeek(Jeek* newJeek)
{
	jeeks.push_back(newJeek);
}

void User::printJeeks()
{
	for(int i = 0; i < jeeks.size(); i++)
		jeeks[i]->print();
}

void User::addUserComment(Comment* comment)
{
	userComments.push_back(comment);
}

void User::addUserReply(Reply* comment)
{
	userReplies.push_back(comment);
}

Message* User::getMessage(std::string id)
{
	for(int i = 0; i < jeeks.size(); i++)
	{
		if(jeeks[i]->getId() == id)
			return jeeks[i];
	}

	for(int i = 0; i < userComments.size(); i++)
	{
		if(userComments[i]->getId() == id)
			return userComments[i];
	}

	for(int i = 0; i < userReplies.size(); i++)
	{
		if(userReplies[i]->getId() == id)
			return userReplies[i];
	}
	return NULL;
}

void User::addFollower(User* follower)
{
	int followerIndex = findFollowerIndex(follower);

	if(followerIndex != NOT_FOUND)
		return;
	else
		followers.push_back(follower);
}

void User::addFollowing(User* following)
{
	int followingIndex = findFollowingIndex(following);

	if(followingIndex != NOT_FOUND)
		return;
	else
		followings.push_back(following);
}

void User::removeFollower(User* follower)
{
	int followerIndex = findFollowerIndex(follower);

	if(followerIndex == NOT_FOUND)
		throw User_404_Exception();
	else
		followers.erase(followers.begin() + followerIndex);
}

void User::removeFollowing(User* following)
{
	int followingIndex = findFollowingIndex(following);

	if(followingIndex != NOT_FOUND)
		return;
	else
		followings.erase(followings.begin() + followingIndex);
}

void User::addNotification(std::string notification)
{
	notifications.push_back(notification);
}

void User::showNotifications()
{
	for(int i = 0; i < notifications.size(); i++)
		std::cout << notifications[i];

	notifications.clear();
}

int User::findFollowingIndex(const User* following)
{
	for(int i = 0; i < followings.size(); i++)
	{
		if(followings[i]->getUsername() == following->getUsername())
			return i;
	}
	return NOT_FOUND;
}

int User::findFollowerIndex(const User* follower)
{
	for(int i = 0; i < followers.size(); i++)
	{
		if(followers[i]->getUsername() == follower->getUsername())
			return i;
	}
	return NOT_FOUND;
}
