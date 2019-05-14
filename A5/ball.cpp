#include "ball.hpp"
Ball::Ball(int x ,int y){
	this->x = double(x);
	this->y = double(y);
	degree = 90;
	vx = VELOCITY * cos(degree * PI/180);
	vy = -VELOCITY * sin(degree * PI/180);
	mode = NORMAL_BALL;
	//cout << "Vx : "<< vx << "     Vy : " << vy << endl;
}
void Ball::showBall(Window* win){
	if (mode == (NORMAL_BALL))
		win->draw_png(IMG_NORMAL_BALL , x-RADIUS , y-RADIUS , 2*RADIUS , 2*RADIUS);
	else if (mode == (FIRE_BALL))
		win->draw_png(IMG_FIRE_BALL , x-RADIUS , y-RADIUS , 2*RADIUS , 2*RADIUS);
}
void Ball::changePosition(double dt){
	double X = dt*vx;
	double Y = dt*vy;
	x = X + x;
	y = Y + y;
	//cout << "x : "<< x << "     y : " <<y << endl;
}
double Ball::getX(){
	return x;
}
double Ball::getY(){
	return y;
}
double Ball::getVx(){
	return vx;
}
double Ball::getVy(){
	return vy;
}
int Ball::getDegree(){
	return degree;
}
int Ball::getMode(){
	return mode;
}
void Ball::setVx(double vx){
	this->vx = vx;
}
void Ball::setVy(double vy){
	this->vy = vy;
}
void Ball::setX(int x){
	this->x = double(x);
}
void Ball::setY(int y){
	this->y = double(y);
}
void Ball::setDegree(int degree){
	this->degree = degree;
}
void Ball::setMode(int newMode){
	mode = newMode;
}
void Ball::set_v_with_degree(){
	vx = VELOCITY * cos(degree * PI/180);
	vy = -VELOCITY * sin(degree * PI/180);
}
void Ball::showArrow(Window * win){
	win->draw_png(IMG_ARROW , int(x) - 2*RADIUS, int(y) + 3*RADIUS , ARROW_SIZE*3 , ARROW_SIZE , (180 - degree ));
}
void Ball::showNumOfBalls(Window * win , int numOfBalls ){
	win->show_text("x " + int_to_string(numOfBalls) , int(x) - 2*RADIUS  ,  int(y) + 7*RADIUS  , BLACK, BALL_FONT, BALL_FONT_SIZE);
}