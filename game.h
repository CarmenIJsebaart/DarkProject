#ifndef GAME_H
#define GAME_H

#include <vector>
#include "action.h"
#include "game_state.h"
#include "player.h"
#include "program_state.h"
#include "sprites_sfml.h"

class game
{
public:

  game(
    sf::RenderWindow& window,
    sprites_sfml &sprites,
    const int world_size
  );

  const auto& get_players() const noexcept { return m_players; }
  auto& get_players() noexcept { return m_players; }
  auto get_x_world_size() const noexcept { return m_x_world_size; }
  auto get_y_world_size() const noexcept { return m_y_world_size; }
  const sprites_sfml get_sprites() const noexcept { return m_sprites; }
  const sf::RenderWindow& get_window() const noexcept { return m_window; }

  /// @param i the player's index, thus 0 for player 1
  /// Will throw if i does not exist
  void do_action(int i, action any_action);

  void execute();

  Gamestate get_game_state() const noexcept { return m_game_state; }
  Programstate get_program_state() const  noexcept { return m_program_state; }

  void set_program_state(Programstate p) { m_program_state = p; }

  auto set_players(std::vector<player> players) { m_players = players; }

  ///Do a game 'tick', e.g. do this 60 times per second
  void tick();

private:

  sprites_sfml m_sprites;

  ///Current frame, is increased every tick
  int m_frame;

  ///Current state
  Gamestate m_game_state;

  std::vector<player> m_players;

  ///In which state is the program while and directly after the battle?
  Programstate m_program_state;

  sf::RenderWindow m_window;

  ///The size of the world in pixels
  int m_x_world_size;
  int m_y_world_size;

};

#endif // GAME_H
