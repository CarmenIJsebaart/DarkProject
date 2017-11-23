#ifndef GAME_WON_BY_RRH_SCREEN_H
#define GAME_WON_BY_RRH_SCREEN_H

#include <cassert>
#include <SFML/Graphics.hpp>
#include "game_state.h"
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
  Gamestate get_state() const noexcept { return m_state; }

  ///Handle input and show this screen once, to be used in testing only
  void tick();

private:

  sprites_sfml& m_sprites;

  Gamestate m_state;

  ///Window used for displayal
  sf::RenderWindow& m_window;

  ///Show this menu on the screen
  void display();

  ///Process a single event
  void process_event(const sf::Event& event);
};

#endif // GAME_WON_BY_RRH_SCREEN_H
