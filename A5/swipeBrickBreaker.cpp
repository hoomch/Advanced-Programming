#include "swipeBrickBreaker.hpp"
SwipeBrickBreaker::SwipeBrickBreaker() : player() , prePlayer() , table(GAME_BOX_X , GAME_BOX_Y + GAME_BOX_HEIGHT/13*3 , GAME_BOX_WIDTH , GAME_BOX_HEIGHT/13*7) {
	mode = NEWGAME;
  mode_editUserName = SAVE;
  mode_gameOver = NEWG;
  enterpressed_mainMenu = false;
  enterpressed_scoreBoard = false;
  enterpressed_editUserName = false;
  enterpressed_newGame = false;
  enterpressed_gameOver = false;
  quit = false;
  prePlayer = player;
  userIn = false;
  spacepressed = false;
  ticks = 0;
  ballsAdded = 0;
  firePower = false;
  isGameOver = false;
  balls.push_back(Ball(GAME_BOX_X + GAME_BOX_WIDTH/2 , GAME_BOX_Y + GAME_BOX_HEIGHT/13*10));
	win = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
}
void SwipeBrickBreaker::display()
{
  while(quit == false)
  {
    Delay(TICK_DURATION);
    getAndProcessInput();
  }
}
void SwipeBrickBreaker::getAndProcessInput(){
  lastEvent = win->pollForEvent();
  processLastEvent();
}
void SwipeBrickBreaker::processLastEvent(){
  if (lastEvent.type() == QUIT)  
    quit = true;
  else if (enterpressed_mainMenu == false) processMainMenu();
  else if (mode == EDIT_USERNAME) processEditUserName();
  else if (mode == SCOREBOARD) processScoreBoard();
  else if (mode == NEWGAME) processNewGame();
  
}
void SwipeBrickBreaker::processMainMenu(){
  enterpressed_scoreBoard = false;
  enterpressed_newGame = false;
  enterpressed_editUserName = false;
  prePlayer = player;
  showMainMenu();
  if (lastEvent.type() == KEY_PRESS){
    if(lastEvent.pressedKey() == ENTER){
      enterpressed_mainMenu = true;
      if (mode == EXIT) quit = true; 
    }
    else if(lastEvent.pressedKey() == UP && enterpressed_mainMenu == false){
      mode = mode - 1;
      if (mode < 0) mode += 4;
      mode = mode % 4;
    }
    else if(lastEvent.pressedKey() == DOWN && enterpressed_mainMenu == false){
      mode = mode + 1;
      if (mode < 0) mode += 4;
      mode = mode % 4;
    }
  }
}
void SwipeBrickBreaker::processEditUserName(){
  showEditPage();
  if (lastEvent.type() == KEY_PRESS){
    if(lastEvent.pressedKey() == ENTER){
      enterpressed_editUserName = true;
      enterpressed_mainMenu = false;
      if (mode_editUserName == SAVE)
        process_save();
      else if (mode_editUserName == CANCEL)
        process_cancel();
      mode_editUserName = SAVE;
    }
    else if(lastEvent.pressedKey() == UP && enterpressed_editUserName == false){
      mode_editUserName = mode_editUserName - 1;
      if (mode_editUserName < 0) mode_editUserName += 2;
      mode_editUserName = mode_editUserName % 2;
    }
    else if(lastEvent.pressedKey() == DOWN && enterpressed_editUserName == false){
      mode_editUserName = mode_editUserName + 1;
      if (mode_editUserName < 0) mode_editUserName += 2;
      mode_editUserName = mode_editUserName % 2;
    }
    else{
      if(lastEvent.pressedKey() == BACK_SPACE)
        player.get_name()->eraseLastChar();
      else player.get_name()->addChar(lastEvent.pressedKey());    
    }
  }
}
void SwipeBrickBreaker::processScoreBoard(){
  showScoreBoard();
  if (lastEvent.type() == KEY_PRESS){
    if(lastEvent.pressedKey() == ENTER){
      enterpressed_scoreBoard = true;
      enterpressed_mainMenu = false;
      mode = 0;
    }
  }
}
void SwipeBrickBreaker::processNewGame(){
  if (isGameOver == false){
    int whichAction = 0;
    if (player.get_string_name().size() == 0) userIn = false;
    if (userIn == false)  processEditUserName();
    else{
      if (spacepressed == false && ballsAdded != 0) addNewBalls();
      if (spacepressed == false && firePower == true) equipFirePower();
      if (lastEvent.type() == KEY_PRESS){
        if(lastEvent.pressedKey() == SPACE && spacepressed == false){
          for (int i=0 ; i<balls.size();i++)
            balls[i].set_v_with_degree();
          spacepressed = true;
        }
        else if (lastEvent.pressedKey() == LEFT && spacepressed == false){
          if (balls[0].getDegree() <= 175){
            for (int i=0;i<balls.size();i++)
            balls[i].setDegree(balls[i].getDegree() + 1);
          }
          for (int i=0 ; i<balls.size();i++)
            balls[i].set_v_with_degree();
        }
        else if (lastEvent.pressedKey() == RIGHT && spacepressed == false){
          if (balls[0].getDegree() >= 10){
            for (int i=0;i<balls.size();i++)
            balls[i].setDegree(balls[i].getDegree() - 8);
          }
          for (int i=0 ; i<balls.size();i++)
            balls[i].set_v_with_degree();
        }
      }
      whichAction = showGamePage();
      if (whichAction == LIFEBALL)  ballsAdded++;
      else if (whichAction == FIREBALL) firePower = true;
    }
  }
  else processGameOver();
}
void SwipeBrickBreaker::processGameOver(){
  showGameOver();
  if (lastEvent.type() == KEY_PRESS){
    if(lastEvent.pressedKey() == ENTER){
      enterpressed_gameOver = true;
      enterpressed_mainMenu = false;
      isGameOver = false;
      if (mode_gameOver == NEWG)
        processNewGame();  
    }
    else if(lastEvent.pressedKey() == UP && enterpressed_gameOver == false){
      mode_gameOver = mode_gameOver - 1;
      if (mode_gameOver < 0) mode_gameOver += 2;
      mode_gameOver = mode_gameOver % 2;
    }
    else if(lastEvent.pressedKey() == DOWN && enterpressed_gameOver == false){
      mode_gameOver = mode_gameOver + 1;
      if (mode_gameOver < 0) mode_gameOver += 2;
      mode_gameOver = mode_gameOver % 2;
    }
  }
}
void SwipeBrickBreaker::showMainMenu(){
  win->clear();
  win->draw_bg(BACKGROUND, 0, 0);
  vector <RGB> rgbs(4 , WHITE);
  setModeColor(rgbs);

  win->fill_rect(NEWGAME_X, NEWGAME_Y, BOX_X, BOX_Y,rgbs[NEWGAME]);
  win->show_text(NEWGAME_STR, NEWGAME_X + BOX_X/8, NEWGAME_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);

  win->fill_rect(SCOREBOARD_X, SCOREBOARD_Y, BOX_X, BOX_Y,rgbs[SCOREBOARD]);
  win->show_text(SCOREBOARD_STR, SCOREBOARD_X + BOX_X/20, SCOREBOARD_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);

  win->fill_rect(EDIT_USERNAME_X, EDIT_USERNAME_Y, BOX_X, BOX_Y,rgbs[EDIT_USERNAME]);
  win->show_text(EDIT_USERNAME_STR, EDIT_USERNAME_X + BOX_X/8, EDIT_USERNAME_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);

  win->fill_rect(EXIT_X, EXIT_Y, BOX_X, BOX_Y,rgbs[EXIT]);
  win->show_text(EXIT_STR, EXIT_X + BOX_X/3, EXIT_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);
  
  win->update_screen();
}
void SwipeBrickBreaker::showScoreBoard(){
  win->clear();
  win->draw_bg(BACKGROUND, 0, 0);

  win->fill_rect(SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT, WHITE);
  win->fill_rect(INNER_BOX_X, INNER_BOX_Y, INNER_BOX_WIDTH, INNER_BOX_HEIGHT, GRAY);

  win->fill_rect(S_MENU_X, S_MENU_Y, BOX_X, BOX_Y, PINK);

  win->show_text(RECORD, SCORE_BOX_X + 20, SCORE_BOX_Y + 30, BLACK, FONT, RECORD_FONT_SIZE);
  win->show_text(MENU, S_MENU_X + BOX_X/3.2, S_MENU_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);
  showTopPlayers();
  win->update_screen();
}
void SwipeBrickBreaker::showEditPage(){
    win->clear();


  vector <RGB> rgbs(2 , STRONG_GRAY);
  setModeColor_editUsername(rgbs);
  win->draw_bg(BACKGROUND, 0, 0);

  win->fill_rect(EDIT_BOX_X, EDIT_BOX_Y, EDIT_BOX_WIDTH, EDIT_BOX_HEIGHT, WHITE);

  win->show_text("Enter Username", TEXT_X, TEXT_Y , BLACK, FONT , FONT_SIZE);
  win->fill_rect(INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, GRAY);

  win->fill_rect(SAVE_X, SAVE_Y, BOX_X, BOX_Y, rgbs[SAVE]);
  win->show_text(SAVE_STR,  SAVE_X + BOX_X/3.2, SAVE_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);
  win->fill_rect(CANCEL_X, CANCEL_Y, BOX_X, BOX_Y, rgbs[CANCEL]);
  win->show_text(CANCEL_STR, CANCEL_X + BOX_X/3.2, CANCEL_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);
  showPlayerName();
  win->update_screen();
}
int SwipeBrickBreaker::showGamePage(){
  int whichAction = 0;
  win->clear();
  win->draw_bg(BACKGROUND, 0, 0);

  win->fill_rect(GAME_BOX_X-2, GAME_BOX_Y-2, GAME_BOX_WIDTH+4, GAME_BOX_HEIGHT+4, WHITE);
  win->draw_line(GAME_BOX_X-2 , GAME_BOX_Y-2 , GAME_BOX_X-2 , GAME_BOX_Y+GAME_BOX_HEIGHT+2 , BLACK );
  win->draw_line(GAME_BOX_X-2 , GAME_BOX_Y-2 , GAME_BOX_X+GAME_BOX_WIDTH+2 , GAME_BOX_Y-2 , BLACK );
  win->draw_line(GAME_BOX_X+GAME_BOX_WIDTH+2 , GAME_BOX_Y-2 , GAME_BOX_X+GAME_BOX_WIDTH+2 , GAME_BOX_Y + GAME_BOX_HEIGHT +2 , BLACK );
  win->draw_line(GAME_BOX_X-2 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*3/13-2 , GAME_BOX_X+1 + GAME_BOX_WIDTH ,  GAME_BOX_Y-2+GAME_BOX_HEIGHT*3/13-2 , BLACK );
  win->draw_line(GAME_BOX_X-2 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*10/13+10 , GAME_BOX_X+1 + GAME_BOX_WIDTH , GAME_BOX_Y-2+GAME_BOX_HEIGHT*10/13+10 , BLACK );
  
  win->show_text("Name : " + player.get_string_name() , GAME_BOX_X-2 + 5 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*0/13 , BLACK , FONT , FONT_SIZE_GAME );
  win->show_text("Score : " + int_to_string(player.get_score() ) , GAME_BOX_X-2 + 5 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*1/13 , BLACK , FONT , FONT_SIZE_GAME );
  win->show_text("Record : " + int_to_string(player.get_record() ) , GAME_BOX_X-2 + 5 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*2/13 , BLACK , FONT , FONT_SIZE_GAME );
  
  table.showTable(win);
  for (int i=0;i<balls.size();i++)
    balls[i].showBall(win);
  if(spacepressed == false) {
    balls[0].showArrow(win);
    balls[0].showNumOfBalls(win , balls.size());
    ticks = 0;
  }
  if (spacepressed == true){
    ticks ++ ;
    int moveableBalls = int(ticks / 20) + 1;
    if (moveableBalls > balls.size()) moveableBalls = balls.size();
    for (int i=0 ; i<moveableBalls;i++){
      balls[i].changePosition();
    } 
    whichAction = table.checkBallPosition(spacepressed , firePower , balls);
    int afterTurn = table.after_turn(player.get_score()+1);
    player.set_score(player.get_score() + afterTurn);
    if (player.get_record() < player.get_score())
      player.set_record(player.get_score());
    if (afterTurn == -1){
      isGameOver = 1;
      player.set_score(player.get_score() + 1);
    }
  }
  win->update_screen();
  return whichAction;
}
void SwipeBrickBreaker::showGameOver(){
  win->clear();
  vector <RGB> rgbs(2 , WHITE);
  setModeColor_gameOver(rgbs);
  win->draw_bg(BACKGROUND, 0, 0);

  win->fill_rect(GAME_BOX_X-2, GAME_BOX_Y-2, GAME_BOX_WIDTH+4, GAME_BOX_HEIGHT+4, GAMEOVER_COLOR);
  win->show_text("GAME OVER :D" ,GAME_BOX_X-2 + 30 , GAME_BOX_Y-2+GAME_BOX_HEIGHT*3/13-2 ,WHITE , FONT ,  50  );

  win->fill_rect(NEW_X, NEW_Y, BOX_X, BOX_Y, rgbs[0]);
  win->show_text(NEW,  NEW_X + BOX_X/3.2 - 30, NEW_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);
  win->fill_rect(RETURN_MENU_X, RETURN_MENU_Y, BOX_X, BOX_Y, rgbs[1]);
  win->show_text(RETURN_MENU, RETURN_MENU_X + BOX_X/3.2, RETURN_MENU_Y + BOX_Y/3.2, LIGHTBLUE, FONT, MENU_FONT_SIZE);

  win->update_screen();
}
void SwipeBrickBreaker::setModeColor(vector <RGB> &rgbs){
  rgbs[mode] = PINK; 
}
void SwipeBrickBreaker::setModeColor_editUsername(vector <RGB> &rgbs){
  rgbs[mode_editUserName] = PINK;
}
void SwipeBrickBreaker::setModeColor_gameOver(vector <RGB> &rgbs){
  rgbs[mode_gameOver] = PINK;
}
void SwipeBrickBreaker::showTopPlayers(){
  int counter ;
  if (users.size() > 0){
      if (users.size() < TOP_RECORDS) counter = users.size();
      else counter = TOP_RECORDS;
      vector <int> topRecords(counter , INVALID);
      for (int i = 0;i < counter ; i++) topRecords[i] = users[i].get_record();
      for (int i = 0;i < counter ; i++){
        int top_id = findTop(topRecords);
        users[top_id].printNameAndRecord(win , INNER_BOX_X + 10 , INNER_BOX_Y , i+1 , COL_HEIGHT , FONT , USER_FONT_SIZE );
      }
  }
}
void SwipeBrickBreaker::showPlayerName(){
  if (player.get_name()->getString().size() != 0 )
    player.get_name()->drawString(win , INPUT_BOX_X + 10 , INPUT_BOX_Y + INPUT_BOX_HEIGHT/4);
  win->update_screen();
}
void SwipeBrickBreaker::process_save(){
  if (player.get_name()->getString().size() != 0 ){
    int user_id = search_user(player.get_name()->getString());
    if (user_id == INVALID) users.push_back(player);
    else player = users[user_id];
    prePlayer = player;
    userIn = true;
  }
}
void SwipeBrickBreaker::process_cancel(){
  player = prePlayer;
}
int SwipeBrickBreaker::search_user(string username){
  int id = INVALID;
  for (int i=0;i<users.size();i++){
    if (users[i].get_name()->getString() == username) 
      id = i; 
  }
  return id;
}
int SwipeBrickBreaker::findTop(vector <int> &topRecords){
    if (topRecords.size() == 0) return INVALID;
    int top_id = INVALID;
    int top_score = INVALID;
    for (int i=0;i<topRecords.size();i++){
        if (topRecords[i] > top_score){
            top_score = topRecords[i];
            top_id = i;
        }
    }
    topRecords[top_id] = INVALID - 1;
    return top_id;
}
void SwipeBrickBreaker::addNewBalls(){
  for (int i=0;i<ballsAdded;i++)  balls.push_back(Ball(balls[0].getX(),balls[0].getY()));
    ballsAdded = 0;
}
void SwipeBrickBreaker::equipFirePower(){
  for (int i=0;i<balls.size();i++)  balls[i].setMode(FIRE_BALL);
}