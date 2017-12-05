#ifndef GAME_WON_BY_RRH_SCREEN_H
#define GAME_WON_BY_RRH_SCREEN_H

#include <cassert>
#include <SFML/Graphics.hpp>
#include "program_state.h"
#include "sprites_sfml.h"

class game_won_by_RRH_screen
{
public:

  game_won_by_RRH_screen(
    sf::RenderWindow& window,
    sprites_sfml& sprites
  );

  void execute();

  ///Obtain the current or state after execute
  Programstate get_state() const noexcept { return m_program_state; }

  ///Handle input and show this screen once, to be used in testing only
  void tick();

private:

  Programstate m_program_state;

  sprites_sfml& m_sprites;

  ///Window used for displayal
  sf::RenderWindow& m_window;

  ///Show this menu on the screen
  void display();

  ///Process a single event
  void process_event(const sf::Event& event);
};

#endif // GAME_WON_BY_RRH_SCREEN_H

