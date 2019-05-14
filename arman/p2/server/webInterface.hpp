#ifndef __WEB_INTERFACE_H__
#define __WEB_INTERFACE_H__

#include "../utils/utilities.hpp"
#include "server.hpp"

#include "../JeekJeek/jeekJeek.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define DEFAULT_SESSION_ID "123"

class WebInterface
{
public: 
    static JeekJeek* jeekJeek;
    static string getHomeHtml(string sessionId);
    static string getRandomSessionId(std::string username);
    static string getJeeksDetailHtml(string sessionId, string jeekId);
    static string getSearchHtml(string keyword);
    static std::string getJeekInfo(Jeek* jeek);
    static int getHash(const std::string& str);
};

class ShowPage : public RequestHandler 
{
    string filePath;

    public:
    ShowPage(string _filePath) { filePath = _filePath; }
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        string body = readFile(filePath.c_str());
        res->setBody(readFile(filePath.c_str()));
        return res;
    }
};

class ShowImage : public RequestHandler 
{
    string filePath;
public:
    ShowImage(string _filePath) { filePath = _filePath; }
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        res->setHeader("Content-Type", "image/png");
        string body = readFile(filePath.c_str());
        res->setBody(body);
        return res;
    }
};

class LoginHandler : public RequestHandler 
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string username = req->getBodyParam("username");
        string password = req->getBodyParam("password");
        cout << "Received Data: " << username << " - " << password << endl;
        res->setHeader("Content-Type", "text/html");
        std::string randomSessionId = WebInterface::getRandomSessionId(username);

        try
        {
            WebInterface::jeekJeek->login(username, password, randomSessionId);
        }
        catch(...)
        {
            res->setBody(readFile("htmlFiles/wrongPassword.html"));
            return res;
        }

        res->setSessionId(randomSessionId);
        res->setBody(WebInterface::getHomeHtml(randomSessionId));
        return res;
    }
};

class SignupHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string username = req->getBodyParam("username");
        string displayname = req->getBodyParam("displayname");
        string password = req->getBodyParam("password");
        cout << "Received Data: " << username << " - " << displayname << "-" << password << endl;
        res->setHeader("Content-Type", "text/html");

        try
        {
            WebInterface::jeekJeek->signup(username, displayname, password);
        }
        catch(...)
        {
            res->setBody(readFile("htmlFiles/userExists.html"));
            return res;
        }

        res->setBody(readFile("htmlFiles/login.html"));
        return res;
    }
};


class HomeHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getHomeHtml(req->getSessionId()));

        return res;
    }
};

class JeekDetailHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string jeekId = req->getBodyParam("jeekId");
        cout << "Received Data: " << jeekId << endl;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getJeeksDetailHtml(req->getSessionId(), jeekId));

        return res;
    }
};

class LikeHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string jeekId = req->getBodyParam("jeekId");
        WebInterface::jeekJeek->like(req->getSessionId(), jeekId);
        
        cout << "Received Data: " << jeekId << endl;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getJeeksDetailHtml(req->getSessionId(), jeekId));
        
        return res;
    }
};

class DislikeHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string jeekId = req->getBodyParam("jeekId");
        WebInterface::jeekJeek->dislike(req->getSessionId(), jeekId);

        cout << "Received Date: " << jeekId << endl;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getJeeksDetailHtml(req->getSessionId(), jeekId));

        return res;
    }
};

class RejeekHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string jeekId = req->getBodyParam("jeekId");
        WebInterface::jeekJeek->rejeek(req->getSessionId(), jeekId);
        
        cout << "Received Data: " << jeekId << endl;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getJeeksDetailHtml(req->getSessionId(), jeekId));
        
        return res;
    }
};

class LogoutHandler : public RequestHandler 
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        
        WebInterface::jeekJeek->logout(req->getSessionId());
        res->setSessionId(DEFAULT_SESSION_ID);

        res->setBody(readFile("htmlFiles/firstPage.html"));
        return res;
    }
};

class SearchHandler : public RequestHandler
{
public:
    Response *callback(Request *req) 
    {
        Response *res = new Response;
        string keyword = req->getBodyParam("keyword");
        
        cout << "Received Data: " << keyword << endl;
        res->setHeader("Content-Type", "text/html");
        res->setBody(WebInterface::getSearchHtml(keyword));
        
        return res;
    }
};

#endif