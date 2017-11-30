#include "game_won_by_rrh_screen.h"
#include <string>
#include "game.h"

game_won_by_RRH_screen::game_won_by_RRH_screen(
  sf::RenderWindow &window,
  sprites_sfml &sprites
) : m_sprites(sprites),
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
  assert(m_state == Gamestate::game_won_by_RRH);

  while(m_window.isOpen()) {
    sf::Event event;
    while(m_window.pollEvent(event))
    {
      process_event(event);
    }
    display();
    //Quit
    if(m_state == Gamestate::quit) return;
    //Go back to first menu
    if(m_state == Gamestate::home) return;
    //Stay here
    assert(m_state == Gamestate::game_won_by_RRH);
  }
}

void game_won_by_RRH_screen::process_event(const sf::Event& event)
{
  switch(event.type) //!OCLINT will not switch on all cases: there are too many of those
  {
    case sf::Event::Closed:
      m_state = Gamestate::quit;
      break;
    case sf::Event::KeyPressed:
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
      {
        m_state = Gamestate::home;
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
      {
        m_state = Gamestate::quit;
      }
      break;
    default:
      break;
  }
}

