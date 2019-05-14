#ifndef __USER_H__
#define __USER_H__

#include "jeek.hpp"
#include "comment.hpp"
#include "reply.hpp"
#include <string>
#include <vector>

#define NOT_FOUND -1

class User
{
public:
	User(std::string _username, std::string _Displayname, std::string _password);
	std::string getUsername() const { return username; }
	std::string getDisplayname() const { return Displayname; }
	std::vector<User*> getFollowers() { return followers; }

	Message* getMessage(std::string id);
	bool isPasswordCorrect(std::string _password);
	void addJeek(Jeek* newJeek);
	void addUserComment(Comment* comment);
	void addUserReply(Reply* reply);
	void addFollower(User* follower);
	void addFollowing(User* following);
	void removeFollower(User* follower);
	void removeFollowing(User* following);
	void addNotification(std::string notification);
	void showNotifications();
	void printJeeks();

private:
	std::string username;
	std::string Displayname;
	std::string password;

	std::vector<Comment*> userComments;
	std::vector<Reply*> userReplies;
	std::vector<Jeek*> jeeks;
	std::vector<User*> followers;
	std::vector<User*> followings;
	std::vector<std::string> notifications;
	
	int findFollowerIndex(const User* follower);
	int findFollowingIndex(const User* following);
};

#endif