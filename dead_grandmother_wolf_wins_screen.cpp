#include "dead_grandmother_wolf_wins_screen.h"
#include <string>
#include "game.h"

dead_grandmother_wolf_wins_screen::dead_grandmother_wolf_wins_screen(
  sprites_sfml& sprites,
  sf::RenderWindow& window)
:   m_program_state{Programstate::dead_grandmother_wolf_wins},
    m_sprites(sprites),
    m_window{window}
{
}

void dead_grandmother_wolf_wins_screen::display()
{
  //Clear
  m_window.clear();
  //Picture must be drawn
  m_window.draw(m_sprites.get_dead_grandmother_wolf_wins());
  //Show
  m_window.display();
}

void dead_grandmother_wolf_wins_screen::execute()
{
  assert(m_program_state == Programstate::dead_grandmother_wolf_wins);

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
    assert(m_program_state == Programstate::dead_grandmother_wolf_wins);
  }
}

void dead_grandmother_wolf_wins_screen::process_event(const sf::Event& event)
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


