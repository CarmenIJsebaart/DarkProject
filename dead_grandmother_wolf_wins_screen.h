#ifndef DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H
#define DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H

#include <cassert>
#include <SFML/Graphics.hpp>
#include "program_state.h"
#include "sprites_sfml.h"

class dead_grandmother_wolf_wins_screen
{
public:
  dead_grandmother_wolf_wins_screen(
    sprites_sfml &sprites,
    sf::RenderWindow& window
  );

  ///Get the current state of the program
  Programstate get_state() const noexcept { return m_program_state; }

  void execute();

private:

  ///The current state of the program
  Programstate m_program_state;

  ///Sprites
  sprites_sfml& m_sprites;

  ///Window used for displayal
  sf::RenderWindow& m_window;

  ///Show this menu on the screen
  void display();

  ///Process a single event
  void process_event(const sf::Event& event);
};

#endif // DEAD_GRANDMOTHER_WOLF_WINS_SCREEN_H
