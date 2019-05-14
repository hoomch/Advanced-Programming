#include "jeekJeek.hpp"
#include "exception.hpp"
using namespace std;

JeekJeek::JeekJeek()
{
	currentUser = NULL;
	idMaker = new IdMaker;
}

void JeekJeek::signup(string username, string displayname, string password)
{
	if(findUserIndex(username) != NOT_FOUND)
		throw Duplicate_User_Exception();

	users.push_back(new User(username, displayname, password));
}

void JeekJeek::login(string username, string password)
{	
	if(isUserLoggedIn())
		throw Logged_In_Exception();

	int userIndex = findUserIndex(username);

	if(userIndex == NOT_FOUND)
	{
		throw Wrong_User_Password_Exception();
	}
	else
	{
		if(users[userIndex]->isPasswordCorrect(password))
			currentUser = users[userIndex];
		else
			throw Wrong_User_Password_Exception();
	}
}

void JeekJeek::logout()
{
	if(currentUser == NULL)
		throw User_404_Exception();
	else
		currentUser	= NULL;
}

void JeekJeek::addJeek(string text, vector<string> inHashtags, vector<string> inMentions)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	if(text.size() > TEXT_MAX_LENGTH)
		throw Long_Text_Exception();

	string newJeekId = idMaker->getJeekId(); 
	Jeek* newJeek = new Jeek(currentUser, text, newJeekId);
	int hashtagIndex, mentionedIndex;

	for(int i = 0; i < inHashtags.size(); i++)
	{
		hashtagIndex = findHashtagIndex(inHashtags[i]);

		if(hashtagIndex == NOT_FOUND)
		{
			Hashtag* newHashtag = new Hashtag(newJeek, inHashtags[i]);
			hashtags.push_back(newHashtag);
			newJeek->addHashtag(newHashtag);
		}
		else
		{
			newJeek->addHashtag(hashtags[hashtagIndex]);
			hashtags[hashtagIndex]->addJeek(newJeek);
		}
	}

	for(int i = 0; i < inMentions.size(); i++)
	{
		mentionedIndex = findUserIndex(inMentions[i]);

		if(mentionedIndex != NOT_FOUND)
		{
			string notification = currentUser->getUsername() + " mentioned you in " + newJeekId	+ '\n';
			users[mentionedIndex]->addNotification(notification);
			newJeek->addMention(users[mentionedIndex]);
		}
	}

	std::vector<User*> followers = currentUser->getFollowers();
	string notification = currentUser->getUsername() + " jeeked " + newJeekId + '\n';

	for(int i = 0; i < followers.size(); i++)
		followers[i]->addNotification(notification);

	currentUser->addJeek(newJeek);
}

void JeekJeek::search(std::string keyword)
{
	if(keyword[0] == '#')
		printHashtag(keyword.substr(1));

	else if(keyword[0] == '@')
		printUser(keyword.substr(1));

	else
		throw Bad_Command_Exception();
}

void JeekJeek::printUser(string username)
{
	int userIndex = findUserIndex(username);

	if(userIndex == NOT_FOUND)
		throw User_404_Exception();
	else
		users[userIndex]->printJeeks();
}

void JeekJeek::printHashtag(string hashtag)
{
	int hashtagIndex = findHashtagIndex(hashtag);
	
	if(hashtagIndex == NOT_FOUND)
		throw Hashtag_404_Exception();
	else
		hashtags[hashtagIndex]->printJeeks();
}

void JeekJeek::addComment(std::string jeekId, std::string text)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	Jeek* jeek = dynamic_cast<Jeek*>(getMessage(jeekId));

	if(jeek == NULL)
		throw Jeek_404_Exception();

	Comment* newComment = new Comment(currentUser, text, idMaker->getCommentId());
	currentUser->addUserComment(newComment);
	jeek->addComment(newComment);

	string notification = currentUser->getUsername() + " commented on " + jeekId + '\n';
	(jeek->getOwner())->addNotification(notification);
}

void JeekJeek::addReply(std::string id, std::string text)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	Message* message = getMessage(id);

	if(dynamic_cast<Jeek*>(message) != NULL)
		throw Bad_Command_Exception();

	if(message == NULL)
		throw Message_404_Exception();

	Reply* newReply = new Reply(currentUser, text, idMaker->getReplyId());
	message->addReply(newReply);
	currentUser->addUserReply(newReply);

	string notification = currentUser->getUsername() + " replied " + id + '\n';
	(message->getOwner())->addNotification(notification);
}

void JeekJeek::rejeek(std::string jeekId)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	Jeek* jeek = dynamic_cast<Jeek*>(getMessage(jeekId));

	if(jeek == NULL)
		throw Jeek_404_Exception();
	else
		jeek->increaseRejeeks();

	Jeek* newJeek = new Jeek(currentUser, "Rejeeked " + jeek->getText(), idMaker->getJeekId());
	vector<Hashtag*> hashtags = jeek->getHashtags();
	vector<User*> mentions = jeek->getMentionedUsers();

	for(int i = 0; i < hashtags.size(); i++)
		hashtags[i]->addJeek(newJeek);

	newJeek->addHashtags(hashtags);
	newJeek->addMentions(mentions);
	currentUser->addJeek(newJeek);

	string notification = currentUser->getUsername() + " rejeeked " + jeekId + '\n';
	(jeek->getOwner())->addNotification(notification);
}

void JeekJeek::showJeek(std::string jeekId)
{
	const Jeek* jeek = dynamic_cast<Jeek*>(getMessage(jeekId));
	
	if(jeek == NULL)
		throw Jeek_404_Exception();
	else
		jeek->showJeek();
}

void JeekJeek::showComment(std::string commentId)
{
	const Comment* comment = dynamic_cast<Comment*>(getMessage(commentId));

	if(comment == NULL)
		throw Message_404_Exception();
	else
		comment->showMessage();
}

void JeekJeek::showReply(std::string replyId)
{
	const Reply* reply = dynamic_cast<Reply*>(getMessage(replyId));

	if(reply == NULL)
		throw Message_404_Exception();
	else
		reply->showMessage();
}


void JeekJeek::like(std::string jeekId)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	Jeek* jeek = dynamic_cast<Jeek*>(getMessage(jeekId));

	if(jeek == NULL)
		throw Jeek_404_Exception();
	else
		jeek->addLike(currentUser);

	string notification = currentUser->getUsername() + " liked " + jeekId + '\n';
	(jeek->getOwner())->addNotification(notification);

}

void JeekJeek::dislike(std::string jeekId)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	Jeek* jeek = dynamic_cast<Jeek*>(getMessage(jeekId));

	if(jeek == NULL)
		throw Jeek_404_Exception();
	else
		jeek->deleteLike(currentUser);

	string notification = currentUser->getUsername() + " disliked " + jeekId + '\n';
	(jeek->getOwner())->addNotification(notification);
}

void JeekJeek::follow(std::string username)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	int followingIndex = findUserIndex(username);

	if(followingIndex == NOT_FOUND)
	{
		throw User_404_Exception();
	}
	else
	{
		currentUser->addFollowing(users[followingIndex]);
		users[followingIndex]->addFollower(currentUser);
	}
}

void JeekJeek::unfollow(std::string username)
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	int followingIndex = findUserIndex(username);

	if(followingIndex == NOT_FOUND)
	{
		throw User_404_Exception();
	}
	else
	{
		currentUser->removeFollowing(users[followingIndex]);
		users[followingIndex]->removeFollower(currentUser);
	}
}

int JeekJeek::findUserIndex(string username)
{
	for(int i = 0; i < users.size(); i++)
	{
		if(users[i]->getUsername() == username)
			return i;
	}
	return NOT_FOUND;
}

int JeekJeek::findHashtagIndex(string hashtag)
{
	for(int i = 0; i < hashtags.size(); i++)
	{
		if(hashtags[i]->getTitle() == hashtag)
			return i;
	}
	return NOT_FOUND;
}

Message* JeekJeek::getMessage(std::string id)
{
	Message* message = NULL;

	for(int i = 0; i < users.size(); i++)
	{
		message = users[i]->getMessage(id);
		
		if(message != NULL)
			break;
	}
	return message;
}

void JeekJeek::showNotifications()
{
	if(!isUserLoggedIn())
		throw Not_Logged_In_Exception();

	currentUser->showNotifications();
}

bool JeekJeek::isUserLoggedIn()
{
	return currentUser != NULL;
}