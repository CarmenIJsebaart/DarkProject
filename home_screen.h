#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "program_state.h"

class home_screen
{
public:

  home_screen(
    sf::RenderWindow& window
  );

  ///Runs this menu, which is handling input and displayal.
  ///Closes when the user wants to quit
  ///or continue to the next menu screen
  ///This can be obtained with the do_quit member function
  void execute();

  ///Obtain the current or state after execute
  Programstate get_state() const noexcept { return m_program_state; }

private:

  ///The font for all texts
  sf::Font m_font;

  ///The lower text
  sf::Text m_begin_text;

  ///In which state is the program while and directly after this menu?
  Programstate m_program_state;

  ///Window used for displayal
  sf::RenderWindow& m_window;

  ///Show this menu on the screen
  void display();

  ///Process a single event
  void process_event(const sf::Event& event);
};

#endif // HOME_SCREEN_H
