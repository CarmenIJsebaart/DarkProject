#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

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

  sf::Texture RRH;
  RRH.loadFromFile("CandlePicture_redhood.png");
  sf::Sprite RRH_sprite(RRH);
  //Centre of the picture
  RRH_sprite.setOrigin(327, 323);
  //Centre + position on screen
  RRH_sprite.setPosition(527, 523);

  sf::Texture WOLF2;
  WOLF2.loadFromFile("CandlePicture_wolf2.png");
  sf::Sprite WOLF_sprite2(WOLF2);
  //Centre of the picture
  WOLF_sprite2.setOrigin(327, 323);
  //Centre + position on screen
  WOLF_sprite2.setPosition(527, 523);

  sf::Texture RRH2;
  RRH2.loadFromFile("CandlePicture_redhood2.png");
  sf::Sprite RRH_sprite2(RRH2);
  //Centre of the picture
  RRH_sprite2.setOrigin(327, 323);
  //Centre + position on screen
  RRH_sprite2.setPosition(527, 523);

  sf::Texture WOLF;
  WOLF.loadFromFile("CandlePicture_wolf.png");
  sf::Sprite WOLF_sprite(WOLF);
  //Centre of the picture
  WOLF_sprite.setOrigin(327, 323);
  //Centre + position on screen
  WOLF_sprite.setPosition(527, 523);

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

  //Choose a random quadrant
  int quad_RRH = rand() % 4;
  int quad_WOLF = rand() % 4;
  while(quad_RRH == quad_WOLF)
  {
    quad_WOLF = rand() % 4;
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

  while(w.isOpen())
  {
    sf::Event event;

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
            RRH_sprite.setRotation(180);
            view1.move(0, 10);
            RRH_sprite.move(0, 10);
            RRH_sprite2.move(0, 10);
            assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          {
            RRH_sprite.setRotation(90);
            view1.move(10, 0);
            RRH_sprite.move(10, 0);
            RRH_sprite2.move(10, 0);
            assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
          {
            RRH_sprite.setRotation(0);
            view1.move(0, -10);
            RRH_sprite.move(0, -10);
            RRH_sprite2.move(0, -10);
            assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
          {
            RRH_sprite.setRotation(270);
            view1.move(-10, 0);
            RRH_sprite.move(-10, 0);
            RRH_sprite2.move(-10, 0);
            assert(RRH_sprite.getPosition() == RRH_sprite2.getPosition());
          }
          //Player 2
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
            WOLF_sprite.setRotation(180);
            view2.move(0, 10);
            WOLF_sprite.move(0, 10);
            WOLF_sprite2.move(0, 10);
            assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            WOLF_sprite.setRotation(90);
            view2.move(10, 0);
            WOLF_sprite.move(10, 0);
            WOLF_sprite2.move(10, 0);
            assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            WOLF_sprite.setRotation(0);
            view2.move(0, -10);
            WOLF_sprite.move(0, -10);
            WOLF_sprite2.move(0, -10);
            assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            WOLF_sprite.setRotation(270);
            view2.move(-10, 0);
            WOLF_sprite.move(-10, 0);
            WOLF_sprite2.move(-10, 0);
            assert(WOLF_sprite.getPosition() == WOLF_sprite2.getPosition());
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
    w.draw(RRH_sprite);

    w.setView(view2);
    w.draw(map);
    w.draw(RRH_sprite2);
    w.draw(WOLF_sprite);

    w.display();
  }
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
