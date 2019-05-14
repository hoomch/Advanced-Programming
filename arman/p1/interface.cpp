#include "interface.hpp"
using namespace std;

Interface::Interface()
{
	jeekJeek = new JeekJeek;
}

void Interface::start()
{
	string command;

	while(getline(cin, command))
	{
		processCommand(command);
	}
}

void Interface::processCommand(string command)
{
	string option;
	stringstream commandSS;
	commandSS << command;
	commandSS >> option;

	try
	{
		if(option == "signup")
		{
			processSignup(getWords(commandSS));
		}
		else if(option == "login")
		{
			processLogin(getWords(commandSS));
		}
		else if(option == "logout")
		{
			jeekJeek->logout();
		}
		else if(option == "jeek")
		{
			processJeek();
		}
		else if(option == "search")
		{
			processSearch(getWords(commandSS));
		}
		else if(option == "comment")
		{
			processComment(getWords(commandSS));
		}
		else if(option == "reply")
		{
			processReply(getWords(commandSS));
		}
		else if(option == "rejeek")
		{
			processRejeek(getWords(commandSS));
		}
		else if(option == "showJeek")
		{
			processShowJeek(getWords(commandSS));
		}
		else if(option == "showComment")
		{
			processShowComment(getWords(commandSS));
		}
		else if(option == "showReply")
		{
			processShowReply(getWords(commandSS));
		}
		else if(option == "like")
		{
			processLike(getWords(commandSS));
		}
		else if(option == "dislike")
		{
			processDislike(getWords(commandSS));
		}
		else if(option == "follow")
		{
			processFollow(getWords(commandSS));
		}
		else if(option == "unfollow")
		{
			processUnfollow(getWords(commandSS));
		}
		else if(option == "notifications")
		{
			jeekJeek->showNotifications();
		}
		else
		{
			throw Bad_Command_Exception();
		}
		std::cout << "Command Ok\n";
	}

	catch(Bad_Command_Exception)
	{
		cerr << "Error: Wrong Command\n";
	}
	catch(Duplicate_User_Exception)
	{
		cerr << "Error: User already exists\n";
	}
	catch(Wrong_User_Password_Exception)
	{
		cerr << "Error: Wrong username or password\n";
	}
	catch(User_404_Exception)
	{
		cerr << "Error: User was not found\n";
	}
	catch(Long_Text_Exception)
	{
		cerr << "Error: Text size must not contain more than 140 characters\n";
	}
	catch(Jeek_404_Exception)
	{
		cerr << "Error: Jeek was not found\n";
	}
	catch(Message_404_Exception)
	{
		cerr << "Error: Message was not found\n";
	}
	catch(Hashtag_404_Exception)
	{
		cerr << "Error: Hashtag was not found\n";
	}
	catch(Logged_In_Exception)
	{
		cerr << "Error: User is already logged in\n";
	}
	catch(Not_Logged_In_Exception)
	{
		cerr << "Error: User is not logged in\n";
	}
	catch(Duplicate_Like_Exception)
	{
		cerr << "Error: Jeek is already liked\n";
	}
	catch(Not_Liked_Exception)
	{
		cerr << "Error: Jeek is not liked\n";
	}
	catch(...)
	{
		cerr << "Error: Unexcepted exception occured!\n";
	}
}	

void Interface::processSignup(std::vector<std::string> words)
{
	if(words.size() != 3)
		throw Bad_Command_Exception();
	
	std::string username = words[0];
	std::string displayname = words[1];
	std::string password = words[2];

	jeekJeek->signup(username, displayname, password);
}

void Interface::processLogin(std::vector<std::string> words)
{
	if(words.size() != 2)
		throw Bad_Command_Exception();

	std::string username = words[0];
	std::string password = words[1];
	
	jeekJeek->login(username, password);
}

void Interface::processJeek()
{
	vector<string> hashtags;
	vector<string> mentionedUsers;
	string option, jeekCommand, text, hashtagText, mentionedUser;

	while(getline(cin, jeekCommand))
	{
		stringstream jeekCommandSS;
		jeekCommandSS << jeekCommand;
		jeekCommandSS >> option;

		while(jeekCommandSS.peek() == ' ') 
			jeekCommandSS.get();

		try
		{
			if(option == "abort")
			{
				return;	
			}
			else if(option == "publish")
			{
				break;
			}
			else if (option == "text")
			{
				getline(jeekCommandSS, text);
			}
			else if(option == "tag")
			{
				jeekCommandSS >> hashtagText;

				if(jeekCommandSS.eof())
					hashtags.push_back(hashtagText);
				else
					throw Bad_Command_Exception();
			}
			else if (option == "mention")
			{
				jeekCommandSS >> mentionedUser;

				if(jeekCommandSS.eof())
					mentionedUsers.push_back(mentionedUser);
				else
					throw Bad_Command_Exception();
			}
			else
			{
				throw Bad_Command_Exception();
			}
		}
		catch(Bad_Command_Exception) 
		{
			cout << "Wrong command\n";
		}
	}

	jeekJeek->addJeek(text, hashtags, mentionedUsers);
}

void Interface::processSearch(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->search(words[0]);
}

void Interface::processComment(std::vector<std::string> words)
{
	if(words.size() < 2)
		throw Bad_Command_Exception();

	std::string jeekId = words[0];
	std::string text = "";

	for(int i = 1; i < words.size(); i++)
		text += words[i] + ' ';

	jeekJeek->addComment(jeekId, text);
}

void Interface::processReply(std::vector<std::string> words)
{
	if(words.size() < 2)
		throw Bad_Command_Exception();

	std::string id = words[0];
	std::string text = "";

	for(int i = 1; i < words.size(); i++)
		text += words[i] + ' ';

	jeekJeek->addReply(id, text);
}

void Interface::processRejeek(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->rejeek(words[0]);
}

void Interface::processShowJeek(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->showJeek(words[0]);
}

void Interface::processShowComment(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->showComment(words[0]);
}

void Interface::processShowReply(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->showReply(words[0]);
}

void Interface::processLike(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->like(words[0]);
}

void Interface::processDislike(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->dislike(words[0]);
}

void Interface::processFollow(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->follow(words[0]);
}

void Interface::processUnfollow(std::vector<std::string> words)
{
	if(words.size() != 1)
		throw Bad_Command_Exception();

	jeekJeek->unfollow(words[0]);
}

std::vector<std::string> Interface::getWords(std::stringstream &commandSS)
{
	std::string word;
	std::vector<std::string> words;

	while(!commandSS.eof())
	{
		commandSS >> word;
		words.push_back(word);
	}
	return words;
}