#include "table.hpp"
Table::Table(int X , int Y , int W , int H ){
	x = X;
	y = Y;
	width = W;
	height = H;
	for (int a = 0;a < COLS ; a++){
		vector <Block> col;
		for (int i=0;i<ROWS;i++)	col.push_back(Block(EMPTY , 0 , x + a * BLOCK_WIDTH , y + i * BLOCK_HEIGHT));
		blocks.push_back(col);
	}
	srand (time(NULL));
	arrivedBalls = 0;
	fireCatched = false;
	rowsDown = 0;
	pullRowsDown(0);
}
void Table::showTable(Window * win){
	for (int i=0 ; i<COLS ; i++)
		for (int j=0 ; j<ROWS-1 ; j++)
			blocks[i][j].showBlock(win);
}
int Table::checkBallPosition(bool &spacepressed ,bool & firePower, vector<Ball> & balls){
	int mode = 0;
	vector<vector<bool> > percussions(ROWS,vector<bool> (COLS));
	for (int a=0 ; a<COLS ; a++)
		for (int b=0 ; b<ROWS-1 ; b++)	percussions[a][b] = false;
	for (int a=0 ; a<COLS ; a++){
		for (int b=0 ; b<ROWS-1 ; b++){
			for (int i=0;i<balls.size();i++){
				if (percussions[a][b] == false){
					int whichPercussion = blocks[a][b].checkPercussion(&balls[i]);
					if (whichPercussion == BOMB){
						deleteBomb(balls , a , b);
					}
					if (whichPercussion){
						percussions[a][b]==true;
						mode = whichPercussion;
					}
				}
			}
		}
	}
	if (mode == FIREBALL)	fireCatched = true;
	bool is_percussion = false;
	for (int i=0;i<balls.size();i++){ 	
		if (balls[i].getX() > x + width ){
			double vx = -balls[i].getVx();
			int X = 2*(x + width) - balls[i].getX();
			int degree = balls[i].getDegree();
			degree = 180 - degree;
			balls[i].setDegree(degree);
			balls[i].setVx(vx);
			balls[i].setX(X);
			is_percussion = true;
		}
		if (balls[i].getY() < y ){
			double vy = -balls[i].getVy();
			int Y = 2*(y) - balls[i].getY();
			int degree = balls[i].getDegree();
			degree = 360 - degree;
			balls[i].setDegree(degree);
			balls[i].setVy(vy);
			balls[i].setY(Y);
			is_percussion = true;
		}
		if (balls[i].getX() < x ){
			double vx = -balls[i].getVx();
			int X = 2*(x) - balls[i].getX();
			int degree = balls[i].getDegree();	
			degree = 540 - degree;
			balls[i].setDegree(degree);
			balls[i].setVx(vx);
			balls[i].setX(X);
			is_percussion = true;
		}
		if (balls[i].getY() > y + height ){
			double vy = 0;
			double vx = 0;
			int Y = 2*(y + height) - balls[i].getY();
			balls[i].setDegree(90);
			balls[i].setVy(vy);
			balls[i].setVx(vx);
			balls[i].setY(Y);
			arrivedBalls ++;
			if (arrivedBalls == 1)	setMainCoordinates(balls[i]);
			if (arrivedBalls == balls.size()){ 
				setBallsCoordinates(balls);
				spacepressed = false;
				arrivedBalls = 0;
				score = 1;
			}
		}	
	}
	if (is_percussion && balls[0].getMode() == FIRE_BALL){
		for (int i=0;i<balls.size();i++){
			balls[i].setDegree(90);
			balls[i].setVy(0);
			balls[i].setVx(0);
			balls[i].setX(x + width/2);
			balls[i].setY(y + height);
			spacepressed = false;
			score = 1;
		}	
			unequipFirePower(balls , firePower);
	}
	return mode;
}
void Table::setBallsCoordinates(vector<Ball> & balls){
	double X = mainX;
	double Y = mainY;
	for (int i=0 ; i<balls.size();i++){
		balls[i].setX(X);
		balls[i].setY(Y);
	}
}
void Table::setMainCoordinates(Ball ball){
	mainX = ball.getX();
	mainY = ball.getY(); 
}
void Table:: deleteBomb(vector<Ball> & balls , int a , int b){
	int minCol = a+2 , minRow = b+2;
	int startCol = a-1 , startRow = b-1;	
	if (minCol>COLS) minCol = COLS;
	if (minRow>ROWS-1) minRow = ROWS-1;
	if (startCol < 0) startCol = 0;
	if (startRow < 0) startRow = 0;
	for (int k=startCol;k<minCol;k++)
	for (int l=startRow;l<minRow;l++){
		blocks[k][l].add_lowered(blocks[k][l].get_resistance());
		blocks[k][l].set_resistance(0);
		if (blocks[k][l].get_mode() == BOMB){
			blocks[k][l].set_mode(EMPTY);
			deleteBomb(balls , k , l);
		}
		
	}
}
void Table::unequipFirePower(vector<Ball> & balls , bool & firePower){
	for (int i=0;i<balls.size();i++)	balls[i].setMode(NORMAL_BALL);
	firePower = false;
}
int Table::after_turn(int playerScore){
	if (score == 1){
		score = 0;
		if (pullRowsDown(playerScore))
			return 1;
		else return -1;
	}
	else return 0;
}
bool Table::pullRowsDown(int playerScore){
	bool continue_game = 1;
	for (int i=0;i<COLS;i++){
		if (continue_game){
			for (int j=ROWS-2;j>0;j--){
				if (j == ROWS - 2 && (blocks[i][j].get_mode() == BRICK || blocks[i][j].get_mode() == BOMB )){
					continue_game = 0;
					break;
				}
				blocks[i][j] = blocks[i][j-1];
			}
		}
	}
	if (continue_game){
		if (rowsDown % 5 < 3){
			int random1 = rand() % COLS;
			int random2 = rand() % COLS;
			random2 = (random1 + random2) % COLS;
			for (int i=0;i<COLS;i++){
				blocks[i][0].set_mode(EMPTY);
				blocks[i][0].set_resistance(0);
			}
			blocks[random1][0].set_mode(BRICK);
			blocks[random1][0].set_resistance(playerScore + 1);
			blocks[random2][0].set_mode(BRICK);
			blocks[random2][0].set_resistance(playerScore + 1);
			for (int i=0;i<COLS;i++){
				if (i!= random1 && i!= random2){
					int R = rand() % 10;
					blocks[i][0].setType(R);
				}
			}
		}
		else if (rowsDown % 5 == 3){
			int random1 = rand() % COLS;
			for (int i=0;i<COLS;i++){
				blocks[i][0].set_mode(EMPTY);
				blocks[i][0].set_resistance(0);
			}
			blocks[random1][0].set_mode(BRICK);
			blocks[random1][0].set_resistance(playerScore + 1);
			for (int i=0;i<COLS;i++){
				if (i!= random1){
					int R = rand() % 10;
					blocks[i][0].setType(R);
				}
			}
		}
		else if (rowsDown % 5 == 4){
			int random1 = rand() % COLS;
			for (int i=0;i<COLS;i++){
				blocks[i][0].set_mode(BRICK);
				blocks[i][0].set_resistance(playerScore + 1);
			}
			int R = rand() % 10;
			blocks[random1][0].setType(R);
		}
		rowsDown ++;
	}
	return continue_game ; 
}
