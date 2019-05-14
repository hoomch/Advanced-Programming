#include <iostream>
#include "webInterface.hpp"
using namespace std;

void doTest();

int main(int argc, char **argv) \
{
    srand(time(NULL));
    doTest();

    try {
        Server server(argc > 1 ? atoi(argv[1]) : 5000);
        server.get("/home_icon", new ShowImage("htmlFiles/home.png"));
        server.get("/not_liked_icon", new ShowImage("htmlFiles/NotLiked.png"));
        server.get("/liked_icon", new ShowImage("htmlFiles/Liked.png"));
        server.get("/rejeek_icon", new ShowImage("htmlFiles/rejeek.png"));
        server.get("/background", new ShowImage("htmlFiles/background.jpg"));
        server.get("/JeekJeekLogoWithText", new ShowImage("htmlFiles/JeekJeekLogoWithText.png"));
        server.get("/search_icon", new ShowImage("htmlFiles/searchicon.png"));
        server.get("/JeekJeekLogo", new ShowImage("htmlFiles/JeekJeekLogo.png"));
        server.get("/404_logo", new ShowImage("htmlFiles/404.png"));

        server.get("/", new ShowPage("htmlFiles/firstPage.html"));
        server.get("/home", new HomeHandler());
        server.get("/login_page", new ShowPage("htmlFiles/login.html"));
        server.get("/signup_page", new ShowPage("htmlFiles/signup.html"));
        server.get("/jeekDetail", new ShowPage("htmlFiles/jeekDetail.html"));
        server.get("/logout", new LogoutHandler());

        server.post("/jeekDetail", new JeekDetailHandler());
        server.post("/login", new LoginHandler());
        server.post("/signup", new SignupHandler());
        server.post("/like", new LikeHandler());
        server.post("/dislike", new DislikeHandler());
        server.post("/rejeek", new RejeekHandler());
        server.post("/search", new SearchHandler());
        server.run();
    } catch (Server::Exception e) {
        cout << e.getMessage() << endl;
    }
}

void doTest()
{
    WebInterface::jeekJeek->signup("arman", "arman", "123456");
    WebInterface::jeekJeek->signup("ali", "ali", "123456");
    WebInterface::jeekJeek->signup("reza", "reza", "123456");

    string sessionId1 = WebInterface::getRandomSessionId("arman");
    string sessionId2 = WebInterface::getRandomSessionId("ali");
    string sessionId3 = WebInterface::getRandomSessionId("reza");

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    WebInterface::jeekJeek->login("arman", "123456", sessionId1);
    vector<string> hashtags1 {"firstJeek", "good_morning"}; 
    vector<string> mentions1 {"arman"};
    vector<string> hashtags2 {"ap", "good_morning", "final_project"}; 
    vector<string> mentions2 {"reza"};

    WebInterface::jeekJeek->addJeek("Hello everyone! This is my first jeek!", hashtags1, mentions1, sessionId1);
    WebInterface::jeekJeek->addJeek("Second Jeek!", hashtags2, mentions2, sessionId1);

    WebInterface::jeekJeek->logout(sessionId1);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WebInterface::jeekJeek->login("ali", "123456", sessionId2);
    vector<string> hashtags3 {"IamReza", "good_morning"}; 
    vector<string> mentions3 {"reza", "ali"};
    vector<string> hashtags4 {"quotes", "stephen_hawking"}; 
    vector<string> mentions4{"reza", "arman", "ali"};

    WebInterface::jeekJeek->addJeek("My name is Reza ('_')", hashtags3, mentions3, sessionId2);
    WebInterface::jeekJeek->addJeek("the greatest enemy of knowledge is not ignorance; it is illusion of knowledge", hashtags4, mentions4, sessionId2);

    WebInterface::jeekJeek->logout(sessionId2);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    WebInterface::jeekJeek->login("reza", "123456", sessionId3);
    vector<string> hashtags5 {"arch_enemy", "alissa_white", "metal"}; 
    vector<string> mentions5 {"arman"};
    vector<string> hashtags6 {"mark_zuckerberg", "facebook", "hah", "iKnowYourInfo"}; 
    vector<string> mentions6{"arman", "reza", "ali"};
    vector<string> hashtags7 {"TA", "ap", "beCool", "doesItWork"}; 
    vector<string> mentions7{"arman"};

    WebInterface::jeekJeek->addJeek("Alissa White has the best voice <3 :)", hashtags5, mentions5, sessionId3);
    WebInterface::jeekJeek->addJeek("Hey JeekJeek manager! Are you a mark zuckerberg too ?!", hashtags6, mentions6, sessionId3);
    WebInterface::jeekJeek->addJeek("Dear Ta! Please be cool with arman's project! Thanks!", hashtags7, mentions7, sessionId3);

    WebInterface::jeekJeek->logout(sessionId3);
}
