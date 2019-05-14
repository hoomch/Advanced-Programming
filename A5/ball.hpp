#ifndef __BALL_H__
#define __BALL_H__

#include "libraries.hpp"
#include "globalFunctions.hpp"
#define IMG_NORMAL_BALL "assets/ball.png"
#define IMG_FIRE_BALL "assets/fireBall.png"
#define IMG_ARROW "assets/arrow.jpg"
#define BALL_FONT "assets/Digitalt.ttf"
#define BALL_FONT_SIZE 20 
#define ARROW_SIZE 10
#define RADIUS 8
#define MISTAKE 2
#define VELOCITY 15
#define PI 3.141592
#define NORMAL_BALL 0
#define FIRE_BALL 1

using namespace std;

class Ball{
private:
	double x;
	double y;
	double vx;
	double vy;
	int degree;
	int mode;
public:
	Ball(int x ,int y);
	void showBall(Window* win);
	void changePosition(double dt = 0.1);
	double getX();
	double getY();
	double getVx();
	double getVy();
	int getDegree();
	int getMode();
	void setX(int x);
	void setY(int y);
	void setVx(double vx);
	void setVy(double vy);
	void setDegree(int degree);
	void setMode(int newMode);
	void set_v_with_degree();
	void showArrow(Window * win);
	void showNumOfBalls(Window * win , int numOfBalls );
};
#endif