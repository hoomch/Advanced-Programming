#ifndef __SBB_H__
#define __SBB_H__

#include"libraries.hpp"
#include "user.hpp"
#include "block.hpp"
#include "ball.hpp"
#include "table.hpp"
#include "globalFunctions.hpp"
using namespace std;
//window
#define WINDOW_WIDTH 350
#define WINDOW_HEIGHT 600
#define TICK_DURATION 3
#define WINDOW_TITLE "Swipe Brick Breaker !"
#define FONT "assets/Digitalt.ttf"
#define BACKGROUND "assets/background.jpg"
//modes
#define NEWGAME 0
#define SCOREBOARD 1
#define EDIT_USERNAME 2
#define EXIT 3
//main menu
#define NEWGAME_STR "New Game"
#define SCOREBOARD_STR "Score Board"
#define EDIT_USERNAME_STR "Edit Name"
#define EXIT_STR "Quit"

#define EXIT_X 75
#define EXIT_Y 475
#define EDIT_USERNAME_X 75
#define EDIT_USERNAME_Y 325
#define SCOREBOARD_X 75
#define SCOREBOARD_Y 175
#define NEWGAME_X 75
#define NEWGAME_Y 25
#define MENU_FONT_SIZE 35
//score board
#define SCORE_BOX_X 25
#define SCORE_BOX_Y 50
#define SCORE_BOX_WIDTH 300
#define SCORE_BOX_HEIGHT 540

#define INNER_BOX_X 60
#define INNER_BOX_Y 125
#define INNER_BOX_WIDTH 230
#define INNER_BOX_HEIGHT 350
#define COL_HEIGHT 40

#define S_MENU_X 75
#define S_MENU_Y 480

#define MENU "Menu"
#define RECORD "Records :" 
#define RECORD_FONT_SIZE 30
#define USER_FONT_SIZE 25

#define TOP_RECORDS 5  
//edit username
#define EDIT_BOX_X 25
#define EDIT_BOX_Y 30
#define EDIT_BOX_WIDTH 300
#define EDIT_BOX_HEIGHT 540

#define TEXT_X 60
#define TEXT_Y 75 

#define INPUT_BOX_X 75
#define INPUT_BOX_Y 150
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 50

#define SAVE_X 75
#define SAVE_Y 250
#define CANCEL_X 75
#define CANCEL_Y 400

#define SAVE_STR "Save"
#define CANCEL_STR "Cancel"

#define SAVE 0
#define CANCEL 1
//new game
#define GAME_BOX_X 12
#define GAME_BOX_Y 7
#define GAME_BOX_WIDTH 325
#define GAME_BOX_HEIGHT 585

#define FONT_SIZE_GAME 23

#define NEW_X 75
#define NEW_Y 250
#define RETURN_MENU_X 75
#define RETURN_MENU_Y 400
#define NEW "New Game"
#define RETURN_MENU "MENU"
#define NEWG 0
#define R_MENU 1
//extras
#define ENTER 13
#define UP 82
#define DOWN 81
#define LEFT 80
#define RIGHT 79
#define BACK_SPACE 8
#define SPACE 32
#define FONT_SIZE 35
#define BOX_X 200
#define BOX_Y 100
#define INVALID -1




const RGB LIGHTBLUE(0, 200, 255);
const RGB PINK(230, 205, 255);
const RGB GRAY(220,220,220);
const RGB STRONG_GRAY(150,150,150);
const RGB GAMEOVER_COLOR(255,51,153);


class SwipeBrickBreaker{
private:
	vector <User> users;

	User player;
	User prePlayer;
	bool userIn;

	Table table;
	vector<Ball> balls;
	int mode;
	int mode_editUserName;
	int mode_scoreBoard;
	int mode_NewGame;
	int mode_gameOver;

	int ballsAdded;
	bool enterpressed_mainMenu;
	bool enterpressed_scoreBoard;
	bool enterpressed_editUserName;
	bool enterpressed_newGame;
	bool enterpressed_gameOver;
	bool spacepressed;
	bool isGameOver;

	bool firePower;
	bool quit;

	int ticks;

	Window * win;
	Event lastEvent;
public:
	SwipeBrickBreaker();

	void setModeColor(vector <RGB> &rgbs);
	void setModeColor_editUsername(vector <RGB> &rgbs);
	void setModeColor_gameOver(vector <RGB> &rgbs);
	void showTopPlayers();
	void showPlayerName();
	void process_save();
	void process_cancel();
	int search_user(string username);
	int findTop(vector <int> &topRecords);
	void addNewBalls();
	void equipFirePower();

    void getAndProcessInput();
    void processLastEvent();
    void processMainMenu();
    void processEditUserName();
   	void processScoreBoard();
 	void processNewGame();
 	void processGameOver();

    void showMainMenu();
    void showScoreBoard();
    void showEditPage();
    int showGamePage();
    void showGameOver();

	void display();
};

#endif