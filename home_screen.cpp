#include "home_screen.h"
#include <cassert>

home_screen::home_screen(
  sf::RenderWindow& window
) : m_font{},
    m_begin_text{},
    m_program_state{Programstate::home},
    m_window{window}
{

  m_font.loadFromFile("arial.ttf");

  //Begin text
  m_begin_text.setFont(m_font);
  m_begin_text.setPosition(sf::Vector2f(0, 125));
  #if SFML_VERSION_MINOR > 3
  m_begin_text.setFillColor(sf::Color::Black);
  #else
  m_begin_text.setColor(sf::Color::Black);
  #endif
  m_begin_text.setCharacterSize(67);
  m_begin_text.setString("Press Space to Start");
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
  assert(m_program_state == Programstate::home);

  while (1)
  {
    //Quit
    if (m_program_state == Programstate::quit) return;
    //Next screen
    if (m_program_state == Programstate::battle) return;
    //Stay here
    assert(m_program_state == Programstate::home);
  }
}

void home_screen::process_event(const sf::Event& event)
{
  switch(event.type) //!OCLINT will not switch on all cases: there are too many of those
  {
    case sf::Event::Closed:
      m_program_state = Programstate::quit;
      break;
    case sf::Event::KeyPressed:
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        m_program_state = Programstate::battle;
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        m_program_state = Programstate::quit;
      }
      break;
    default:
      break;
  }
}
