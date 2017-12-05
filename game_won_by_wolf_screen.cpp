#include "game_won_by_wolf_screen.h"
#include <string>
#include "game.h"

game_won_by_wolf_screen::game_won_by_wolf_screen(
  sf::RenderWindow &window,
  sprites_sfml &sprites
) : m_program_state{Programstate::game_won_by_wolf},
    m_sprites(sprites),
    m_window{window}
{
}

void game_won_by_wolf_screen::display()
{
  //Clear
  m_window.clear(sf::Color::Red);
  //Picture must be drawn
  m_window.draw(m_sprites.get_wolf_wins_sprite());
  //Show
  m_window.display();
}

void game_won_by_wolf_screen::execute()
{
  assert(m_program_state == Programstate::game_won_by_wolf);

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
    assert(m_program_state == Programstate::game_won_by_wolf);
  }
}

void game_won_by_wolf_screen::process_event(const sf::Event& event)
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

