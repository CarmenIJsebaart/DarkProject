#include "program.h"

#include <cassert>
#include "dead_grandmother_wolf_wins_screen.h"
#include "game.h"
#include "game_won_by_rrh_screen.h"
#include "game_won_by_wolf_screen.h"

program::program()
  : m_program_state{Programstate::home},
    m_sprites{},
    m_window{
      sf::VideoMode(800, 400), //Window is 800 x 400 pixels
      "DarkProject",
      sf::Style::Titlebar | sf::Style::Close
    }
{}

program::~program()
{
  m_window.close();
}

void program::run()
{
  while(m_window.isOpen())
  {
    switch(m_program_state)
    {
      case Programstate::home: run_home_screen(); break;
      case Programstate::battle: run_battle(); break;
      case Programstate::dead_grandmother_wolf_wins: run_dead_grandmother_wolf_wins_screen(); break;
      case Programstate::game_won_by_RRH: run_game_won_by_RRH_screen(); break;
      case Programstate::game_won_by_wolf: run_game_won_by_wolf_screen(); break;
      case Programstate::quit: return;
    }
  }
}

void program::run_battle()
{

}

void program::run_home_screen()
{

}

void program::run_dead_grandmother_wolf_wins_screen()
{
  dead_grandmother_wolf_wins_screen m(
    m_window,
    m_sprites
  );
  m.execute();

  //Read the new state from the dialog
  m_program_state = m.get_state();
  if(m_program_state == Programstate::quit) return;
  assert(m_program_state == Programstate::battle);
}

void program::run_game_won_by_RRH_screen()
{
  game_won_by_RRH_screen m(
    m_window,
    m_sprites
  );
  m.execute();

  //Read the new state from the dialog
  m_program_state = m.get_state();
  if(m_program_state == Programstate::quit) return;
  assert(m_program_state == Programstate::battle);
}

void program::run_game_won_by_wolf_screen()
{
  game_won_by_wolf_screen m(
    m_window,
    m_sprites
  );
  m.execute();

  //Read the new state from the dialog
  m_program_state = m.get_state();
  if(m_program_state == Programstate::quit) return;
  assert(m_program_state == Programstate::battle);
}
