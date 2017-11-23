#ifndef DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H
#define DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H

#include <cassert>
#include <SFML/Graphics.hpp>
#include "game_state.h"
#include "sprites_sfml.h"

class dead_grandmother_wolf_wins_screen
{
public:
  dead_grandmother_wolf_wins_screen(
    sprites_sfml &sprites,
    sf::RenderWindow& window
  );

  ///Get the current state of the program
  Gamestate get_state() const noexcept { return m_state; }

  void execute();

private:

  ///The current state of the program
  Gamestate m_state;

  ///Text of which player has won
  sprites_sfml& m_sprites;

  ///Window used for displayal
  sf::RenderWindow& m_window;

  ///Show this menu on the screen
  void display();

  ///Process a single event
  void process_event(const sf::Event& event);
};

#endif // DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H