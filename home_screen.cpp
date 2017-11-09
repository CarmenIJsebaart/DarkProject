#include "home_screen.h"
#include <cassert>

home_screen::home_screen(
  sf::RenderWindow& window
) : m_font{},
    m_begin_text{},
    m_state{Gamestate::home},
    m_window{window}
{

  m_font.loadFromFile("arial.ttf");

  //Begin text
  m_begin_text.setFont(m_font);
  m_begin_text.setPosition(sf::Vector2f(75, 150));
  #if SFML_VERSION_MINOR > 3
  m_begin_text.setFillColor(sf::Color::White);
  #else
  m_begin_text.setColor(sf::Color::White);
  #endif
  m_begin_text.setCharacterSize(60);
  m_begin_text.setString("Press Enter To Start!");
}

void home_screen::display()
{
  //Clear
  m_window.clear();

  //Draw begin text
  m_window.draw(m_begin_text);

  //Show
  m_window.display();
}

void home_screen::execute()
{
  assert(m_state == Gamestate::home);

  while (1)
  {
    //Quit
    if (m_state == Gamestate::quit) return;
    //Next screen
    if (m_state == Gamestate::running) return;
    //Stay here
    assert(m_state == Gamestate::home);
  }
}
