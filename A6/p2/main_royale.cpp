#include "game.hpp"

using namespace std;

int main() {
  Game game;

  ‍game.add_player_card(1, "giant");
  game.add_player_card(1, "witch");
  game.add_player_card(1, "goblin");
  game.add_player_card(1, "dragon");

  game.add_player_card(2, "ghost");
  game.add_player_card(2, "archer");
  game.add_player_card(2, "dragon");
  game.add_player_card(2, "giant");

  game.play();
}
