#include "webInterface.hpp"
#include <vector>
#include <string>
using namespace std;

JeekJeek* WebInterface::jeekJeek = new JeekJeek;

string WebInterface::getHomeHtml(string sessionId)
{
	std::vector<Jeek*> userJeeks = jeekJeek->getUserJeeks(sessionId);

	string code = "<!DOCTYPE html> <html>";
	code += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";

	code += " <head> <style>";
	code += " body{ font-family: \"Arial\"; background-image:url(\"/background\"); background-attachment: fixed; margin:0;}";
	
	code += " a:link:not(#logo), a:visited:not(#logo) { font-family: \"Arial\"; background-color: rgb(54, 98, 114); color: white; padding: 14px 25px; text-decoration: none; display: inline-block; }";

    code += " a:hover:not(#logo), a:active:not(#logo) { background-color: #0099ff; }";

    code += " ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: rgb(40, 32, 66); position: fixed; top: 0; width: 100%;}";

    code += " li { float: left; }";
 
    code += " li a:not(#logo) { display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }";

    code += " li a:hover:not(.active):not(#logo) {  background-color: #0099ff; }";

	code += " input[type=text] { margin-left: 180px; width: 200px; box-sizing: border-box; border: 2px solid #ccc; border-radius: 4px; "; 
	code += " font-size: 16px; background-color: white; background-image: url(\"/search_icon\"); background-position: 10px 10px;";
	code += " background-repeat: no-repeat; padding: 12px 20px 12px 40px; -webkit-transition: width 0.4s ease-in-out; transition: width 0.4s ease-in-out;}";
	code += " input[type=text]:hover { width: 800px; }";
	code += " p:not(#results) { margin-left: 20px; border: 1px solid; width: 70%; border-radius: 5px; display: inline-block; background-color: #f2f2f2; padding: 20px; }";
	code += " .button { background-color: rgb(40, 32, 66); border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }";

    code += " .button:hover { background-color: #0099ff; }";

	code +="</style> </head>";

	code += "<body> <ul> <li> &nbsp <a href=\"/home\" id=\"logo\"> <img src=\"/JeekJeekLogo\" width=\"59px\" height=\"42\"> </a> </li> <li> <form action=\"/search\" method=\"post\"> <input name=\"keyword\" type=\"text\" placeHolder= \"Serach here...\" /> </form> </li> <li style=\"float:right\"> <a href=\"/logout\">Logout</a></li> </ul> <br> <br>";
	
    code += " <p id=\"results\" style=\"margin-left: 20px; font-size: 36px; color: rgb(40, 32, 66); \"> Results: </p> </div>";

	for(int i = userJeeks.size()-1 ; i >= 0; i--)
	{
		code += "<p>";
		code += WebInterface::getJeekInfo(userJeeks[i]);
		code += " </p> ";
		code += "<form action =\"/jeekDetail\" method=\"post\" style=\"margin-left: 20px; \"> <button class=\"button\"; type=\"submit\" name=\"jeekId\" value=\"" + userJeeks[i]->getId() + "\">More Detail</button> </form> <br><br>";
	}
	
	code += " </body> </html>";
	return code;
}

string WebInterface::getJeeksDetailHtml(string sessionId, string jeekId)
{
	std::vector<Jeek*> userJeeks = jeekJeek->getUserJeeks(sessionId);
	Jeek* jeek = jeekJeek->getJeek(jeekId);

	string code = "<!DOCTYPE html> <html>";
	code += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";

	code += " <head> <style>";
	code += " body{ font-family: \"Arial\"; background-image:url(\"/background\"); background-attachment: fixed; margin:0;}";
	
	code += " a:link:not(#logo), a:visited:not(#logo) { font-family: \"Arial\"; background-color: rgb(54, 98, 114); color: white; padding: 14px 25px; text-decoration: none; display: inline-block; }";

    code += " a:hover:not(#logo), a:active:not(#logo) { background-color: #0099ff; }";

    code += " ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: rgb(40, 32, 66); position: fixed; top: 0; width: 100%;}";

    code += " li { float: left; }";
 
    code += " li a:not(#logo) { display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }";

    code += " li a:hover:not(.active):not(#logo) {  background-color: #0099ff; }";

	code += " input[type=text] { margin-left: 180px; width: 200px; box-sizing: border-box; border: 2px solid #ccc; border-radius: 4px; "; 
	code += " font-size: 16px; background-color: white; background-image: url(\"/search_icon\"); background-position: 10px 10px;";
	code += " background-repeat: no-repeat; padding: 12px 20px 12px 40px; -webkit-transition: width 0.4s ease-in-out; transition: width 0.4s ease-in-out;}";
	code += " input[type=text]:hover { width: 800px; }";
	code += " p:not(#details) { margin-left: 20px; border: 1px solid; width: 70%; border-radius: 5px; display: inline-block; background-color: #f2f2f2; padding: 20px; }";
	code += " .button { background-color: rgb(40, 32, 66); border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }";

    code += " .button:hover { background-color: #0099ff; }";

	code +=" </style> </head>";

	code += " <body> <ul> <li> &nbsp <a href=\"/home\" id=\"logo\"> <img src=\"/JeekJeekLogo\" width=\"59px\" height=\"42\"> </a> </li> <li> <form action=\"/search\" method=\"post\"> <input name=\"keyword\" type=\"text\" placeHolder= \"Serach here...\" /> </form> </li> <li style=\"float:right\"> <a href=\"/logout\">Logout</a></li> </ul> <br> <br>";
	
    code += " <p id=\"details\" style=\"margin-left: 20px; font-size: 36px; color: rgb(40, 32, 66); \"> Details: </p> </div>";

	code += "<p>";
	code += WebInterface::getJeekInfo(jeek);
	code += " </p> ";
	code += " <br> ";

	if(jeekJeek->hasLiked(sessionId, jeekId))
		code += "<form action =\"/dislike\" method=\"post\" style=\"display: inline;\"> <button style=\"margin-left: 20px; background: none; border:none;\" class=\"button\"; type=\"submit\" name=\"jeekId\" value=\"" + jeek->getId() + "\"> <img style=\"width:30px; height:30px;\" src=\"/liked_icon\"> </button> </form>";
	else
		code += "<form action =\"/like\" method=\"post\" style=\"display: inline;\"> <button style=\"margin-left: 20px; background: none; border:none;\" class=\"button\"; type=\"submit\" name=\"jeekId\" value=\"" + jeek->getId() + "\"> <img style=\"width:30px; height:30px;\" src=\"/not_liked_icon\"> </button> </form>";

	code += "<form action =\"/rejeek\" method=\"post\" style=\"display: inline;\"> <button style=\"margin-left: 20px; background: none; border:none;\" class=\"button\"; type=\"submit\" name=\"jeekId\" value=\"" + jeek->getId() + "\"> <img style=\"width:30px; height:30px;\" src=\"/rejeek_icon\"> </button> </form>";
	code += "<br> <a style=\"margin-left: 20px; background-color: rgb(40, 32, 66);\" href=\"/home\">Home</a>";
	code += "</body> </html>";
	return code;
}

std::string WebInterface::getRandomSessionId(string username)
{
	return to_string(WebInterface::getHash(username)) + to_string(rand() % 10000);
}

std::string WebInterface::getSearchHtml(string keyword)
{	
	std::vector<Jeek*> jeeks;

	string code = "<!DOCTYPE html> <html>";
	code += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";

	code += " <head> <style>";
	code += " body{ font-family: \"Arial\"; background-image:url(\"/background\"); background-attachment: fixed; margin:0;}";
	
	code += " a:link:not(#logo), a:visited:not(#logo) { font-family: \"Arial\"; background-color: rgb(54, 98, 114); color: white; padding: 14px 25px; text-decoration: none; display: inline-block; }";

    code += " a:hover:not(#logo), a:active:not(#logo) { background-color: #0099ff; }";

    code += " ul { list-style-type: none; margin: 0; padding: 0; overflow: hidden; background-color: rgb(40, 32, 66); position: fixed; top: 0; width: 100%;}";

    code += " li { float: left; }";
 
    code += " li a:not(#logo) { display: block; color: white; text-align: center; padding: 14px 16px; text-decoration: none; }";

    code += " li a:hover:not(.active):not(#logo) {  background-color: #0099ff; }";

	code += " input[type=text] { margin-left: 180px; width: 200px; box-sizing: border-box; border: 2px solid #ccc; border-radius: 4px; "; 
	code += " font-size: 16px; background-color: white; background-image: url(\"/search_icon\"); background-position: 10px 10px;";
	code += " background-repeat: no-repeat; padding: 12px 20px 12px 40px; -webkit-transition: width 0.4s ease-in-out; transition: width 0.4s ease-in-out;}";
	code += " input[type=text]:hover { width: 800px; }";
	code += " p:not(#results) { margin-left: 20px; border: 1px solid; width: 70%; border-radius: 5px; display: inline-block; background-color: #f2f2f2; padding: 20px; }";
	code += " .button { background-color: rgb(40, 32, 66); border: none; color: white; padding: 15px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; cursor: pointer; }";

    code += " .button:hover { background-color: #0099ff; }";

	code +="</style> </head>";

	code += "<body> <ul> <li> &nbsp <a href=\"/home\" id=\"logo\"> <img src=\"/JeekJeekLogo\" width=\"59px\" height=\"42\"> </a> </li> <li> <form action=\"/search\" method=\"post\"> <input name=\"keyword\" type=\"text\" placeHolder= \"Serach here...\" /> </form> </li> <li style=\"float:right\"> <a href=\"/logout\">Logout</a></li> </ul> <br> <br>";
	
    code += " <p id=\"results\" style=\"margin-left: 20px; font-size: 36px; color: rgb(40, 32, 66); \"> Results: </p> </div>";


	if(keyword[0] == '@')
		jeeks = jeekJeek->getUserJeeksByUsername(keyword.substr(1));
	else if(keyword[0] == '#')
		jeeks = jeekJeek->getHashtagJeeks(keyword.substr(1));

	for(int i = jeeks.size()-1 ; i >= 0; i--)
	{
		code += "<p>";
		code += WebInterface::getJeekInfo(jeeks[i]);
		code += " </p> ";
		code += "<form action =\"/jeekDetail\" method=\"post\" style=\"margin-left: 20px;\"> <button class=\"button\"; type=\"submit\" name=\"jeekId\" value=\"" + jeeks[i]->getId() + "\">More Detail</button> </form> <br><br>";
	}

	code += " </body> </html>";
	return code;
}

string WebInterface::getJeekInfo(Jeek* jeek)
{
	std::vector<Hashtag*> hashtags = jeek->getHashtags();
	std::vector<User*> mentionedUsers = jeek->getMentionedUsers();

	stringstream result;

	result << "<b>" + jeek->getOwnerDisplayname() << "</b> <br>";
	result << jeek->getText() << "<br>";

	if(hashtags.size() != 0)
	{
		for(int i = 0; i < hashtags.size(); i++)
			result << '#' << hashtags[i]->getTitle() << ' '; 
		result << "<br>";
	}

	if(mentionedUsers.size() != 0)
	{
		for(int i = 0; i < mentionedUsers.size(); i++)
			result << '@' << mentionedUsers[i]->getUsername() << ' ';
		result << "<br>";
	}

	result << "Likes: " << jeek->getLikesNumber() << "<br>";
	result << "Rejeeks " << jeek->getRejeeksNumber() << "<br>";

	return result.str();
}

int WebInterface::getHash(const string& str)
{
    int hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 2 * hash + (unsigned char)str[i];
    return hash;
}
