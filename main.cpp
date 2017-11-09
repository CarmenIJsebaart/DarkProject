#include <cassert>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "helper.h"
#include "tilemap.h"

////////////////////////////////////////////////////////////
///                                                      ///
///      ----- Red Riding Hood  ------> Big Bad Wolf     ///
///      |            |                       |          ///
///      v            |                       |          ///
///   Hunter          |                       |          ///
///      |            v                       |          ///
///      -------> Grandmother <----------------          ///
///                                                      ///
///  Two player game:                                    ///
///  - Red Riding Hood                                   ///
///  - Big Bad Wolf                                      ///
///                                                      ///
///  Red Riding Hood has to find her Grandmother before  ///
///  the Big Bad Wolf finds Grandmother. If the Big Bad  ///
///  Wolf finds Grandmother first, Red Riding Hood has   ///
///  to find the Hunter to free Grandmother.             ///
///                                                      ///
////////////////////////////////////////////////////////////

bool has_to_die(sf::Vector2f pos1, sf::Vector2f pos2);
sf::Vector2f set_position(const int quad);

int main()
{
  const int w_size_x = 800;
  const int w_size_y = 400;
  sf::RenderWindow w(sf::VideoMode(w_size_x, w_size_y), "DarkProject",
    sf::Style::Titlebar | sf::Style::Close);

  sf::View view1, view2;
  view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
  view1.setSize(w_size_x/2, w_size_y);
  view1.setCenter(0,0);

  view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
  view2.setSize(w_size_x/2, w_size_y);
  view2.setCenter(0,0);

  create_resources();

  sf::Font arial;
  arial.loadFromFile("arial.ttf");

  ///Pictures of players

  ///Red Riding Hood
  sf::Texture RRH;
  RRH.loadFromFile("CandlePicture_redhood.png");
  sf::Sprite RRH_sprite(RRH);
  //Centre of the picture
  RRH_sprite.setOrigin(327, 323);
  //Centre + position on screen
  RRH_sprite.setPosition(527, 523);

  sf::Texture RRH2;
  RRH2.loadFromFile("CandlePicture_redhood2.png");
  sf::Sprite RRH_sprite2(RRH2);
  //Centre of the picture
  RRH_sprite2.setOrigin(327, 323);
  //Centre + position on screen
  RRH_sprite2.setPosition(527, 523);

  ///Wolf
  sf::Texture WOLF;
  WOLF.loadFromFile("CandlePicture_wolf.png");
  sf::Sprite WOLF_sprite(WOLF);
  //Centre of the picture
  WOLF_sprite.setOrigin(327, 323);
  //Centre + position on screen
  WOLF_sprite.setPosition(527, 523);

  sf::Texture WOLF2;
  WOLF2.loadFromFile("CandlePicture_wolf2.png");
  sf::Sprite WOLF_sprite2(WOLF2);
  //Centre of the picture
  WOLF_sprite2.setOrigin(327, 323);
  //Centre + position on screen
  WOLF_sprite2.setPosition(527, 523);

  ///Winner screen pictures

  ///Wolf eats Red Riding Hood
  sf::Texture wolfwins;
  wolfwins.loadFromFile("Wolf_winner_screen.png");
  sf::Sprite wolfwins_sprite(wolfwins);
  wolfwins_sprite.setPosition(0, 0);

  ///Wolf eats Grandmother
  sf::Texture wolfwins2;
  wolfwins.loadFromFile("deadgrandmother_winner_screen.png");
  sf::Sprite wolfwins2_sprite(wolfwins2);
  wolfwins2_sprite.setPosition(0, 0);

  ///Red Riding Hood meets grandmother
  sf::Texture RRHwins;
  RRHwins.loadFromFile("RRH_winner_screen.png");
  sf::Sprite RRHwins_sprite(RRHwins);
  RRHwins_sprite.setPosition(0, 0);

  ///Other pictures

  ///Grandmother picture
  sf::Texture GRANDMOTHER;
  GRANDMOTHER.loadFromFile("Grandmother.png");
  sf::Sprite GRANDMOTHER_sprite(GRANDMOTHER);
  //Center of the picture
  GRANDMOTHER_sprite.setOrigin(12, 12);

  ///Hunter picture
  sf::Texture HUNTER;
  HUNTER.loadFromFile("Hunter.png");
  sf::Sprite HUNTER_sprite(HUNTER);
  //center of the picture
  HUNTER_sprite.setOrigin(12,12);

  ///////////////////////////////////////////////////////
  ///  First choose a quadrant a player has to start  ///
  ///  in. Then choose a random position in this      ///
  ///  quadrant.                                      ///
  ///   ___________________________________________   ///
  ///  |                     |                     |  ///
  ///  |                     |                     |  ///
  ///  |    hor.             |    hor.             |  ///
  ///  |    0-2100           |    3100-5200        |  ///
  ///  |    ver.             |    ver.             |  ///
  ///  |    0-2100           |    0-2100           |  ///
  ///  |                     |                     |  ///
  ///  |_____________________|_____________________|  ///
  ///  |                     |                     |  ///
  ///  |                     |                     |  ///
  ///  |    hor.             |    hor.             |  ///
  ///  |    0-2100           |    3100-5200        |  ///
  ///  |    ver.             |    ver.             |  ///
  ///  |    3100-5200        |    3100-5200        |  ///
  ///  |                     |                     |  ///
  ///  |_____________________|_____________________|  ///
  ///                                                 ///
  ///////////////////////////////////////////////////////

  //Choose a random quadrant for players and grandmother
  int quad_RRH = rand() % 4;
  int quad_WOLF = rand() % 4;
  int quad_GRANDMOTHER = rand() % 4;
  while(quad_RRH == quad_WOLF)
  {
    quad_WOLF = rand() % 4;
  }
  while(quad_WOLF == quad_GRANDMOTHER || quad_RRH == quad_GRANDMOTHER)
  {
    quad_GRANDMOTHER = rand() % 4;
  }

  //Choose a random position in the correct quadrant
  RRH_sprite.setPosition(set_position(quad_RRH));
  sf::Vector2f RRH_pos = RRH_sprite.getPosition();
  RRH_sprite2.setPosition(RRH_pos);
  view1.move(RRH_pos);
  assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
  WOLF_sprite.setPosition(set_position(quad_WOLF));
  sf::Vector2f WOLF_pos = WOLF_sprite.getPosition();
  WOLF_sprite2.setPosition(WOLF_pos);
  view2.move(WOLF_pos);
  assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
  GRANDMOTHER_sprite.setPosition(set_position(quad_GRANDMOTHER));

  // define the level with a vector of tile indices
  std::vector<int> level;

  for(int i = 0; i != 1600; ++i)
  {
    int number = rand() % 4;
    level.push_back(number);
  }

  // create the tilemap from the level definition
  tilemap map;
  if (!map.load("tilemap.png", sf::Vector2u(130, 130), level, 40, 40))
    return -1;

  Gamestate state = Gamestate::running;

  while(w.isOpen())
  {
    sf::Event event;

    while(state == Gamestate::running)
    {
      while(w.pollEvent(event))
      {
        switch(event.type)
        {
          case sf::Event::Closed:
            w.close();
            break;
          case sf::Event::KeyPressed:
            //Player 1
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
              if(RRH_sprite.getPosition().y < 5200)
              {
                RRH_sprite.setRotation(180);
                view1.move(0, 10);
                RRH_sprite.move(0, 10);
                RRH_sprite2.move(0, 10);
                assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
              if(RRH_sprite.getPosition().x < 5200)
              {
                RRH_sprite.setRotation(90);
                view1.move(10, 0);
                RRH_sprite.move(10, 0);
                RRH_sprite2.move(10, 0);
                assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
              if(RRH_sprite.getPosition().y > 0)
              {
                RRH_sprite.setRotation(0);
                view1.move(0, -10);
                RRH_sprite.move(0, -10);
                RRH_sprite2.move(0, -10);
                assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
              if(RRH_sprite.getPosition().x > 0)
              {
                RRH_sprite.setRotation(270);
                view1.move(-10, 0);
                RRH_sprite.move(-10, 0);
                RRH_sprite2.move(-10, 0);
                assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
              }
            }
            //Player 2
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
              if(WOLF_sprite.getPosition().y < 5200)
              {
                WOLF_sprite.setRotation(180);
                view2.move(0, 10);
                WOLF_sprite.move(0, 10);
                WOLF_sprite2.move(0, 10);
                assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
              if(WOLF_sprite.getPosition().x < 5200)
              {
                WOLF_sprite.setRotation(90);
                view2.move(10, 0);
                WOLF_sprite.move(10, 0);
                WOLF_sprite2.move(10, 0);
                assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
              if(WOLF_sprite.getPosition().y > 0)
              {
                WOLF_sprite.setRotation(0);
                view2.move(0, -10);
                WOLF_sprite.move(0, -10);
                WOLF_sprite2.move(0, -10);
                assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
              if(WOLF_sprite.getPosition().x > 0)
              {
                WOLF_sprite.setRotation(270);
                view2.move(-10, 0);
                WOLF_sprite.move(-10, 0);
                WOLF_sprite2.move(-10, 0);
                assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
              }
            }
            break;
        default:
            break;
        }
      }

      w.clear();

      w.setView(view1);
      w.draw(map);
      w.draw(WOLF_sprite2);

      if(!has_to_die(RRH_sprite.getPosition(), WOLF_sprite.getPosition()))
      {
        w.draw(RRH_sprite);
      }

      w.setView(view2);
      w.draw(map);
      if(!has_to_die(RRH_sprite.getPosition(), WOLF_sprite.getPosition()))
      {
        w.draw(RRH_sprite2);
      }
      else
      {
        state = Gamestate::game_won_by_wolf;
      }
      if(!has_to_die(GRANDMOTHER_sprite.getPosition(), WOLF_sprite.getPosition()))
      {
        w.draw(GRANDMOTHER_sprite);
      }
      else
      {
        state = Gamestate::game_won_by_wolf;
      }
      w.draw(WOLF_sprite);
      w.display();
    }
    if(state == Gamestate::game_won_by_wolf)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      wolfwins_sprite.setScale(0.4, 0.6);
      wolfwins_sprite.setPosition(-180, -175);
      w.clear(sf::Color::Red);
      w.draw(wolfwins_sprite);
      w.display();
    }
    if(state == Gamestate::dead_grandmother_wolf_wins)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      wolfwins2_sprite.setScale(0.4, 0.6);
      wolfwins2_sprite.setPosition(-170, -200);
      w.clear(sf::Color::Red);
      w.draw(wolfwins2_sprite);
      w.display();
    }
    if(state == Gamestate::game_won_by_RRH)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      RRHwins_sprite.setScale(0.55, 0.55);
      RRHwins_sprite.setPosition(-120, -120);
      w.clear(sf::Color::Red);
      w.draw(RRHwins_sprite);
      w.display();
    }
  }
}

bool has_to_die(sf::Vector2f pos1, sf::Vector2f pos2)
{
  float dist_x = pos1.x - pos2.x;
  float dist_y = pos1.y - pos2.y;
  float dist_x_2 = dist_x * dist_x;
  float dist_y_2 = dist_y * dist_y;

  float dist = sqrt(dist_x_2 + dist_y_2);

  //75 is a magic number (personal space)
  if(dist <= 75)
  {
    return true;
  }
  return false;
}

sf::Vector2f set_position(const int quad)
{
  if(quad == 0)
  {
    float x = rand() % 2101;
    float y = rand() % 2101;

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 1)
  {
    float x = rand() % 2100 + 3100;
    float y = rand() % 2101;

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 2)
  {
    float x = rand() % 2101;
    float y = rand() % 2100 + 3100;

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 3)
  {
    float x = rand() % 2100 + 3100;
    float y = rand() % 2100 + 3100;

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  return sf::Vector2f(0,0);
}
