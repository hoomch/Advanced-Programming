#include "block.hpp"

Block::Block(int mode , int Resistance , int X , int Y ){
	this->x = X;
	this->y = Y;
	this->mode = mode;
	if (mode == BOMB) this->resistance = 1;
	else if (mode != BRICK ) this->resistance = 0;
	else this->resistance = Resistance; 
	loweredResistance = 0;
}
int Block::get_mode(){
	return mode;
}
void Block::set_mode(int M){
	mode = M;
}
int Block::get_resistance(){
	return resistance;
}
void Block::set_resistance(int R){
	resistance = R;
}
int Block::checkPercussion(Ball * ball){
	int whichPercussion = 0;
	if (ball->getMode() == NORMAL_BALL){
		if (mode == BRICK || mode == BOMB){
			if (ball->getX() >= x && ball->getX() <= x + MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT){
				double vx = -ball->getVx();
				int X = 2*(x) - ball->getX();
				int degree = ball->getDegree();
				degree = 180 - degree;
				ball->setDegree(degree);
				ball->setVx(vx);
				ball->setX(X);
				whichPercussion = mode;
			}
			else if (ball->getY() <= y + BLOCK_HEIGHT && ball->getY() >= y + BLOCK_HEIGHT - MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH){
				double vy = -ball->getVy();
				int Y = 2*(y + BLOCK_HEIGHT) - ball->getY();
				int degree = ball->getDegree();
				degree = 360 - degree;
				ball->setDegree(degree);
				ball->setVy(vy);
				ball->setY(Y);
				whichPercussion = mode;
			}
			else if (ball->getX() <= x + BLOCK_WIDTH && ball->getX() >= x + BLOCK_WIDTH - MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT){
				double vx = -ball->getVx();
				int X = 2*(x + BLOCK_WIDTH) - ball->getX();
				int degree = ball->getDegree();
				degree = 540 - degree;
				ball->setDegree(degree);
				ball->setVx(vx);
				ball->setX(X);
				whichPercussion = mode;
			}
			else if (ball->getY() >= y && ball->getY() <= y + MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH){
				double vy = -ball->getVy();
				int Y = 2*(y) - ball->getY();
				int degree = ball->getDegree();
				degree = 360 - degree;
				ball->setDegree(degree);
				ball->setVy(vy);
				ball->setY(Y);
				whichPercussion = mode;
			}
			if (whichPercussion){
				resistance += -1;
				loweredResistance ++;
			}
		}
		else{
			if ((ball->getX() >= x && ball->getX() <= x + MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT) ||
			(ball->getY() <= y + BLOCK_HEIGHT && ball->getY() >= y + BLOCK_HEIGHT - MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH) ||
			(ball->getX() <= x + BLOCK_WIDTH && ball->getX() >= x + BLOCK_WIDTH - MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT) ||
			(ball->getY() >= y && ball->getY() <= y + MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH)){
				whichPercussion = mode;
				mode = EMPTY;
			}	
		} 
	}
	else if (ball->getMode() == FIRE_BALL){
		if ((ball->getX() >= x && ball->getX() <= x + MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT) ||
			(ball->getY() <= y + BLOCK_HEIGHT && ball->getY() >= y + BLOCK_HEIGHT - MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH) ||
			(ball->getX() <= x + BLOCK_WIDTH && ball->getX() >= x + BLOCK_WIDTH - MISTAKE && ball->getY() >= y && ball->getY() <= y + BLOCK_HEIGHT) ||
			(ball->getY() >= y && ball->getY() <= y + MISTAKE && ball->getX() >= x && ball->getX() <= x + BLOCK_WIDTH)){
				whichPercussion = mode;
				loweredResistance += resistance;
				resistance = 0;
				mode = EMPTY;
		}
	}
	checkFinished();
	return whichPercussion;
}
void Block::showBlock(Window * win){
	if (mode == BRICK){
		win->fill_rect(x+2, y+2, BLOCK_WIDTH-2, BLOCK_HEIGHT-2,BLOCK_COLOR);
		win->show_text(int_to_string(resistance) , x+BLOCK_WIDTH/3 , y+BLOCK_HEIGHT/3.2 , BLACK , BLOCK_FONT , BLOCK_FONT_SIZE );
		
	}
	if (mode == BOMB){
		win->fill_rect(x+2, y+2, BLOCK_WIDTH-2, BLOCK_HEIGHT-2,BLACK);
	}
	else if (mode == FIREBALL){
		win->draw_png(IMG_FIREBALL , x + (BLOCK_WIDTH - BLOCK_HEIGHT)/2 +10 , y + 10 , BLOCK_HEIGHT - 20 , BLOCK_HEIGHT - 20);
	}
	else if (mode == LIFEBALL){
		win->draw_png(IMG_LIFEBALL , x + (BLOCK_WIDTH - BLOCK_HEIGHT)/2 + 10 , y + 10 , BLOCK_HEIGHT - 20, BLOCK_HEIGHT - 20);		
	}
}
void Block::checkFinished(){
	if (mode == BRICK || mode == BOMB)
		if (resistance == 0)	mode = EMPTY;
}
int Block::get_lowered(){
	return loweredResistance;
}
void Block::set_lowered(int L){
	loweredResistance = L ;
}
void Block::add_lowered(int added){
	loweredResistance += added;
}
void Block::operator=(Block & b){
	mode = b.get_mode();
	resistance = b.get_resistance();
}
void Block::setType(int random){
	if (random == 0){
		mode = BOMB;
		resistance = 1;
	}
	else if (random == 1){
		mode = FIREBALL;
		resistance = 0;
	}
	else if (random > 1 && random <= 4){
		mode = LIFEBALL;
		resistance = 0;
	}
	else if (random > 4){
		mode = EMPTY;
		resistance = 0;
	}
}