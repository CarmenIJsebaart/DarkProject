#include "game_won_by_rrh_screen.h"
#include <string>
#include "game.h"

game_won_by_RRH_screen::game_won_by_RRH_screen(
  sf::RenderWindow &window,
  sprites_sfml &sprites
) : m_program_state{Programstate::game_won_by_RRH},
    m_sprites(sprites),
    m_window{window}
{
}

void game_won_by_RRH_screen::display()
{
  //Clear
  m_window.clear();
  //Picture must be drawn
  m_window.draw(m_sprites.get_red_riding_hood_wins());
  //Show
  m_window.display();
}

void game_won_by_RRH_screen::execute()
{
  assert(m_program_state == Programstate::game_won_by_RRH);

  while(m_window.isOpen()) {
    sf::Event event;
    while(m_window.pollEvent(event))
    {
      process_event(event);
    }
    display();
    //Quit
    if(m_program_state == Programstate::quit) return;
    //Go back to first menu
    if(m_program_state == Programstate::home) return;
    //Stay here
    assert(m_program_state == Programstate::game_won_by_RRH);
  }
}

void game_won_by_RRH_screen::process_event(const sf::Event& event)
{
  switch(event.type) //!OCLINT will not switch on all cases: there are too many of those
  {
    case sf::Event::Closed:
      m_program_state = Programstate::quit;
      break;
    case sf::Event::KeyPressed:
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      {
        m_program_state = Programstate::home;
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

