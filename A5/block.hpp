#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "libraries.hpp"
#include "globalFunctions.hpp"
#include "ball.hpp"
#define EMPTY 0
#define BRICK 1
#define BOMB 2
#define LIFEBALL 3
#define FIREBALL 4
#define IMG_LIFEBALL "assets/lifeBall.png"
#define IMG_FIREBALL "assets/firePower.png"
#define BLOCK_FONT "assets/Digitalt.ttf"
#define BLOCK_FONT_SIZE 22

#define BLOCK_WIDTH 65
#define BLOCK_HEIGHT 45
const RGB BLOCK_COLOR(179,0,179);
using namespace std;

class Block{
private:
	int x;
	int y;
	int mode;
	int resistance;
	int loweredResistance;//extra
public:
	Block(int mode , int Resistance  , int X , int Y);
	int get_mode();
	void set_mode(int M);
	int get_resistance();
	void set_resistance(int R);
	int checkPercussion(Ball * ball);
	void showBlock(Window * win);
	void checkFinished();
	int get_lowered();//extra
	void set_lowered(int L = 0);//extra
	void add_lowered(int added);//extra
	void operator=(Block & b);
	void setType(int random);

};

#endif