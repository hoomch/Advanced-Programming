#include "jeekJeek.hpp"
#include "exception.hpp"
using namespace std;

JeekJeek::JeekJeek()
{
	idMaker = new IdMaker;
}

void JeekJeek::login(string username, string password, string sessionId)
{
	int userIndex = findUserIndex(username);

	if(userIndex == NOT_FOUND)
		throw Wrong_User_Password_Exception();

	if(users[userIndex]->isPasswordCorrect(password))
		onlineUsers[sessionId] = users[userIndex];
	else
		throw Wrong_User_Password_Exception();
}

void JeekJeek::signup(string username, string displayname, string password)
{
	if(findUserIndex(username) != NOT_FOUND)
		throw Duplicate_User_Exception();

	users.push_back(new User(username, displayname, password));
}

vector<Jeek*> JeekJeek::getUserJeeksByUsername(string username)
{
	vector<Jeek*> jeeks;

	int userIndex = findUserIndex(username);

	if(userIndex != NOT_FOUND)
		jeeks = users[userIndex]->getJeeks();
		
	return jeeks;
}

vector<Jeek*> JeekJeek::getUserJeeks(string sessionId)
{
	vector<Jeek*> jeeks;
	User* user = onlineUsers[sessionId];

	if(user != NULL)
	{
		jeeks = user->getJeeks();
	}
	return jeeks;
}

vector<Jeek*> JeekJeek::getHashtagJeeks(string hashtag)
{
	vector<Jeek*> jeeks;
	int hashtagIndex = findHashtagIndex(hashtag);

	if(hashtagIndex != NOT_FOUND)
		jeeks = hashtags[hashtagIndex]->getJeeks();

	return jeeks;
}

void JeekJeek::logout(string sessionId)
{
	onlineUsers.erase(sessionId);	
}

void JeekJeek::addJeek(string text, vector<string> inHashtags, vector<string> inMentions, string sessionId)
{
	if(text.size() > TEXT_MAX_LENGTH)
		throw Long_Text_Exception();

	User* user = onlineUsers[sessionId];

	Jeek* newJeek = new Jeek(user, text, idMaker->getJeekId());
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
			newJeek->addMention(users[mentionedIndex]);
	}

	onlineUsers[sessionId]->addJeek(newJeek);
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

void JeekJeek::rejeek(std::string sessionId, std::string jeekId)
{
	User* user = onlineUsers[sessionId];

	Jeek* jeek = getJeek(jeekId);
	jeek->increaseRejeeks();

	Jeek* newJeek = new Jeek(user, "Rejeeked " + jeek->getText(), idMaker->getJeekId());
	vector<Hashtag*> hashtags = jeek->getHashtags();
	vector<User*> mentions = jeek->getMentionedUsers();

	for(int i = 0; i < hashtags.size(); i++)
		hashtags[i]->addJeek(newJeek);

	newJeek->addHashtags(hashtags);
	newJeek->addMentions(mentions);

	user->addJeek(newJeek);
}

Jeek* JeekJeek::getJeek(std::string jeekId)
{
	Jeek* jeek = NULL;

	for(int i = 0; i < users.size(); i++)
	{
		jeek = users[i]->getJeek(jeekId);

		if(jeek != NULL)
			break;
	}
	return jeek;
}

void JeekJeek::like(std::string sessionId, std::string jeekId)
{
	Jeek* jeek = getJeek(jeekId);
	User* user = onlineUsers[sessionId];

	jeek->addLike(user);

}

void JeekJeek::dislike(std::string sessionId, std::string jeekId)
{
	Jeek* jeek = getJeek(jeekId);
	User* user = onlineUsers[sessionId];

	jeek->deleteLike(user);
}

bool JeekJeek::hasLiked(std::string sessionId, std::string jeekId)
{
	Jeek* jeek = getJeek(jeekId);

	return jeek->hasLiker(onlineUsers[sessionId]);
}