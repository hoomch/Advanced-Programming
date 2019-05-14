#include "message.hpp"
#include "user.hpp"
using namespace std;

void Message::addComment(Message* comment)
{
	comments.push_back(comment);
}

void Message::addReply(Message* reply)
{
	replies.push_back(reply);
}

void Message::showCommentsId() const
{
	for(int i = 0; i < comments.size(); i++)
		std::cout << comments[i]->getId() << '\n';
}

void Message::showRepliesId() const
{
	for(int i = 0; i < replies.size(); i++)
		std::cout << replies[i]->getId() << '\n';
}

void Message::showMessage() const
{
	std::cout << user->getDisplayname() << '\n';
	std::cout << text << '\n';
	std::cout << "Replies:\n";
	showRepliesId();
}