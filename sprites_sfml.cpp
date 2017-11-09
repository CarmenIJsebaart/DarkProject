#include "sprites_sfml.h"

#include "helper.h"

sprites_sfml::sprites_sfml()
{
  //Create all resources needed: pictures, etc.
  create_resources();

  //Load player
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("CandlePicture_redhood.png");
    m_RRH_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("CandlePicture_redhood2.png");
    m_RRH_sprite2.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("CandlePicture_wolf.png.png");
    m_wolf_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("CandlePicture_wolf2.png");
    m_wolf_sprite2.setTexture(*texture);
    m_textures.push_back(texture);
  }

  //Load winner screens
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("Wolf_winner_screen.png");
    m_wolf_wins_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("deadgrandmother_winner_screen.png");
    m_dead_grandmother_wolf_wins_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("RRH_winner_screen.png");
    m_RRH_wins_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }

  ///Other pictures
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("Grandmother.png");
    m_grandmother_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }
  {
    sf::Texture * const texture = new sf::Texture;
    texture->loadFromFile("Hunter.png");
    m_hunter_sprite.setTexture(*texture);
    m_textures.push_back(texture);
  }

}

