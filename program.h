#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "sprites_sfml.h"

class program
{

public:
  program();

  ///The main program loop, ends when the user quits
  void run();

private:

  ///All the sprites
  sprites_sfml m_sprites;

  ///The current active state of the program
  Gamestate m_state;

  ///The window used throughout the program
  sf::RenderWindow m_window;

  ///Run the game
  void run_game();

  ///Run the home screen
  void run_home_screen();

  ///Run game won by RRH screen
  void run_game_won_by_RRH_screen();

  ///Run game won by wolf screen
  void run_game_won_by_wolf_screen();

  ///Run wolf ate grandmother screen
  void run_dead_grandmother_wolf_wins_screen();
};

#endif // PROGRAM_H
