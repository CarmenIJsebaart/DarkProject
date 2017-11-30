#include <cassert>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "game_state.h"
#include "helper.h"
#include "sprites_sfml.h"
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

void set_start_position(sf::Sprite &player);
bool has_to_die(sf::Vector2f pos1, sf::Vector2f pos2);
sf::Vector2f set_position(const int quad, const int size);

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

  sprites_sfml sprites;
  sf::Sprite red_riding_hood = sprites.get_red_riding_hood_sprite();
  sf::Sprite red_riding_hood_shadow = sprites.get_red_riding_hood_shadow_sprite();
  sf::Sprite wolf = sprites.get_wolf_sprite();
  sf::Sprite wolf_shadow = sprites.get_wolf_shadow_sprite();

  ///Set starting position of players
  set_start_position(red_riding_hood);
  set_start_position(red_riding_hood_shadow);
  set_start_position(wolf);
  set_start_position(wolf_shadow);

  ///Winner screen pictures

  ///Wolf eats red riding hood
  sf::Sprite wolf_wins_dead_red_riding_hood = sprites.get_wolf_wins_sprite();
  wolf_wins_dead_red_riding_hood.setPosition(0, 0);
  ///Wolf eats Grandmother
  sf::Sprite wolf_wins_dead_grandmother = sprites.get_dead_grandmother_wolf_wins();
  wolf_wins_dead_grandmother.setPosition(0, 0);
  ///Red Riding Hood meets grandmother
  sf::Sprite red_riding_hood_wins = sprites.get_red_riding_hood_wins();
  red_riding_hood_wins.setPosition(0, 0);

  ///Other pictures

  ///Grandmother picture
  sf::Sprite grandmother = sprites.get_grandmother();
  //Center of the picture
  grandmother.setOrigin(12, 12);
  ///Hunter picture
  sf::Sprite hunter = sprites.get_hunter();
  hunter.setOrigin(12,12);

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

  const int n_rows = 20;
  const int n_columns = 20;
  const int block_size = 130;
  const int screen_size = block_size*n_rows;

  //Choose a random position in the correct quadrant
  red_riding_hood.setPosition(set_position(quad_RRH, screen_size));
  sf::Vector2f red_riding_hood_pos = red_riding_hood.getPosition();
  red_riding_hood_shadow.setPosition(red_riding_hood_pos);
  view1.move(red_riding_hood_pos);
  assert(red_riding_hood.getPosition() == red_riding_hood_shadow.getPosition());
  wolf.setPosition(set_position(quad_WOLF, screen_size));
  sf::Vector2f WOLF_pos = wolf.getPosition();
  wolf_shadow.setPosition(WOLF_pos);
  view2.move(WOLF_pos);
  assert(wolf.getPosition() == wolf_shadow.getPosition());
  grandmother.setPosition(set_position(quad_GRANDMOTHER, screen_size));

  // define the level with a vector of tile indices
  std::vector<int> level;

  for(int i = 0; i != n_rows * n_columns; ++i)
  {
    int number = rand() % 4;
    level.push_back(number);
  }

  // create the tilemap from the level definition
  tilemap map;
  if (!map.load("tilemap.png", sf::Vector2u(block_size, block_size), level, n_rows, n_columns))
    return -1;

  std::cout << grandmother.getPosition().x << std::endl;
  std::cout << grandmother.getPosition().y << std::endl;

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
              if(red_riding_hood.getPosition().y < block_size * n_rows)
              {
                red_riding_hood.setRotation(180);
                view1.move(0, 10);
                red_riding_hood.move(0, 10);
                red_riding_hood_shadow.move(0, 10);
                assert(red_riding_hood.getPosition() == red_riding_hood_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
              if(red_riding_hood.getPosition().x < block_size * n_columns)
              {
                red_riding_hood.setRotation(90);
                view1.move(10, 0);
                red_riding_hood.move(10, 0);
                red_riding_hood_shadow.move(10, 0);
                assert(red_riding_hood.getPosition() == red_riding_hood_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
              if(red_riding_hood.getPosition().y > 0)
              {
                red_riding_hood.setRotation(0);
                view1.move(0, -10);
                red_riding_hood.move(0, -10);
                red_riding_hood_shadow.move(0, -10);
                assert(red_riding_hood.getPosition() == red_riding_hood_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
              if(red_riding_hood.getPosition().x > 0)
              {
                red_riding_hood.setRotation(270);
                view1.move(-10, 0);
                red_riding_hood.move(-10, 0);
                red_riding_hood_shadow.move(-10, 0);
                assert(red_riding_hood.getPosition() == red_riding_hood_shadow.getPosition());
              }
            }
            //Player 2
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
              if(wolf.getPosition().y < block_size * n_rows)
              {
                wolf.setRotation(180);
                view2.move(0, 10);
                wolf.move(0, 10);
                wolf_shadow.move(0, 10);
                assert(wolf.getPosition() == wolf_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
              if(wolf.getPosition().x < block_size * n_columns)
              {
                wolf.setRotation(90);
                view2.move(10, 0);
                wolf.move(10, 0);
                wolf_shadow.move(10, 0);
                assert(wolf.getPosition() == wolf_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
              if(wolf.getPosition().y > 0)
              {
                wolf.setRotation(0);
                view2.move(0, -10);
                wolf.move(0, -10);
                wolf_shadow.move(0, -10);
                assert(wolf.getPosition() == wolf_shadow.getPosition());
              }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
              if(wolf.getPosition().x > 0)
              {
                wolf.setRotation(270);
                view2.move(-10, 0);
                wolf.move(-10, 0);
                wolf_shadow.move(-10, 0);
                assert(wolf.getPosition() == wolf_shadow.getPosition());
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
      w.draw(wolf_shadow);

      if(!has_to_die(red_riding_hood.getPosition(), wolf.getPosition()))
      {
        w.draw(red_riding_hood);
      }

      w.setView(view2);
      w.draw(map);
      if(!has_to_die(red_riding_hood.getPosition(), wolf.getPosition()))
      {
        w.draw(red_riding_hood_shadow);
      }
      else
      {
        state = Gamestate::game_won_by_wolf;
      }
      if(!has_to_die(grandmother.getPosition(), wolf.getPosition()))
      {
        w.draw(grandmother);
      }
      else
      {
        state = Gamestate::dead_grandmother_wolf_wins;
      }
      w.draw(wolf);
      w.display();
    }
    if(state == Gamestate::game_won_by_wolf)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      wolf_wins_dead_red_riding_hood.setScale(0.4, 0.6);
      wolf_wins_dead_red_riding_hood.setPosition(-180, -175);
      w.clear(sf::Color::Red);
      w.draw(wolf_wins_dead_red_riding_hood);
      w.display();
    }
    if(state == Gamestate::dead_grandmother_wolf_wins)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      wolf_wins_dead_grandmother.setScale(0.4, 0.6);
      wolf_wins_dead_grandmother.setPosition(-170, -200);
      w.clear(sf::Color::Red);
      w.draw(wolf_wins_dead_grandmother);
      w.display();
    }
    if(state == Gamestate::game_won_by_RRH)
    {
      w.setView(view1);
      view1.setViewport(sf::FloatRect(0, 0, 1, 1));
      view1.setCenter(0, 0);
      red_riding_hood_wins.setScale(0.55, 0.55);
      red_riding_hood_wins.setPosition(-120, -120);
      w.clear(sf::Color::Red);
      w.draw(red_riding_hood_wins);
      w.display();
    }
  }
}

void set_start_position(sf::Sprite &player)
{
  //Centre of the picture
  player.setOrigin(327, 323);
  //Centre + position on screen
  player.setPosition(527, 523);
}

bool has_to_die(sf::Vector2f pos1, sf::Vector2f pos2)
{
  float dist_x = pos1.x - pos2.x;
  float dist_y = pos1.y - pos2.y;
  float dist_x_2 = dist_x * dist_x;
  float dist_y_2 = dist_y * dist_y;

  float dist = sqrt(dist_x_2 + dist_y_2);

  //60 is a magic number (personal space)
  if(dist <= 60)
  {
    return true;
  }
  return false;
}

sf::Vector2f set_position(const int quad, const int size)
{
  if(quad == 0)
  {
    float x = rand() % (size*3/8);
    float y = rand() % (size*3/8);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 1)
  {
    float x = rand() % (size*3/8) + (size*5/8);
    float y = rand() % (size*3/8);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 2)
  {
    float x = rand() % (size*3/8);
    float y = rand() % (size*3/8) + (size*5/8);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  else if(quad == 3)
  {
    float x = rand() % (size*3/8) + (size*5/8);
    float y = rand() % (size*3/8) + (size*5/8);

    sf::Vector2f pos;
    pos.x = x;
    pos.y = y;
    return pos;
  }
  return sf::Vector2f(0,0);
}
