#ifndef __TABLE_H__
#define __TABLE_H__

#include "libraries.hpp"
#include "block.hpp"
#include "globalFunctions.hpp"
#include "ball.hpp"
#define ROWS 7
#define COLS 5
using namespace std;

class Table{
private:
	double x;
	double y;
	double width;
	double height;
	int arrivedBalls;
	double mainX;
	double mainY;
	bool fireCatched;
	int rowsDown;
	int score;
	vector< vector<Block> >  blocks;
public:
	Table(int X , int Y , int W , int H );
	void showTable(Window * win);
	int checkBallPosition(bool & spacepressed , bool & firePower , vector<Ball>& balls );
	void setBallsCoordinates(vector<Ball>& balls);
	void setMainCoordinates(Ball ball);
	void deleteBomb(vector<Ball> & balls , int a , int b);
	void unequipFirePower(vector<Ball> & balls , bool & firePower);
	int after_turn(int playerScore);
	bool pullRowsDown(int playerScore);
};

#endif