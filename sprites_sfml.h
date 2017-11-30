#ifndef SPRITES_SFML_H
#define SPRITES_SFML_H

#include <SFML/Graphics.hpp>

class sprites_sfml
{
public:
  //Prepare all sprites
  sprites_sfml();

  sf::Sprite& get_red_riding_hood_sprite() noexcept { return m_RRH_sprite; }
  sf::Sprite& get_red_riding_hood_shadow_sprite() noexcept { return m_RRH_sprite2; }
  sf::Sprite& get_wolf_sprite() noexcept { return m_wolf_sprite; }
  sf::Sprite& get_wolf_shadow_sprite() noexcept { return m_wolf_sprite2; }
  sf::Sprite& get_wolf_wins_sprite() noexcept { return m_wolf_wins_sprite; }
  sf::Sprite& get_dead_grandmother_wolf_wins() noexcept { return m_dead_grandmother_wolf_wins_sprite; }
  sf::Sprite& get_red_riding_hood_wins() noexcept { return m_RRH_wins_sprite; }
  sf::Sprite& get_grandmother() noexcept { return m_grandmother_sprite; }
  sf::Sprite& get_hunter() noexcept { return m_hunter_sprite; }
  sf::Sprite& get_wall() noexcept { return m_wall_sprite; }

private:

  ///Pictures of players
  sf::Sprite m_RRH_sprite;
  sf::Sprite m_RRH_sprite2;
  sf::Sprite m_wolf_sprite;
  sf::Sprite m_wolf_sprite2;

  ///Winner screen pictures
  sf::Sprite m_wolf_wins_sprite;
  sf::Sprite m_dead_grandmother_wolf_wins_sprite;
  sf::Sprite m_RRH_wins_sprite;

  ///Other pictures
  sf::Sprite m_grandmother_sprite;
  sf::Sprite m_hunter_sprite;
  sf::Sprite m_wall_sprite;

  ///Textures
  std::vector<sf::Texture*> m_textures;
};

std::ostream& operator<<(std::ostream &os, const sprites_sfml&) noexcept;
///Will always return true, because this are the one and only sprites.
bool operator==(const sprites_sfml&, const sprites_sfml&) noexcept;

#endif // SPRITES_SFML_H
