#include <iostream>
#include <SFML/Graphics.hpp>

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

using namespace std;

int main()
{
  const int w_size_x = 800;
  const int w_size_y = 400;
  sf::RenderWindow w(sf::VideoMode(w_size_x, w_size_y), "DarkProject",
    sf::Style::Titlebar | sf::Style::Close);

  sf::View view1, view2;

  view1.setViewport(sf::FloatRect(0, 0, 0.5f, 1));
  view1.setSize(w_size_x/2, w_size_y);

  view2.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
  view2.setSize(w_size_x/2, w_size_y);

  sf::Texture grass;
  grass.loadFromFile("Grass.png");
  sf::Sprite map(grass);

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
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
          {
            RRH_sprite.setRotation(90);
            view1.move(10, 0);
            RRH_sprite.move(10, 0);
            RRH_sprite2.move(10, 0);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
          {
            RRH_sprite.setRotation(0);
            view1.move(0, -10);
            RRH_sprite.move(0, -10);
            RRH_sprite2.move(0, -10);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
          {
            RRH_sprite.setRotation(270);
            view1.move(-10, 0);
            RRH_sprite.move(-10, 0);
            RRH_sprite2.move(-10, 0);
          }
          //Player 2
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
            WOLF_sprite.setRotation(180);
            view2.move(0, 10);
            WOLF_sprite.move(0, 10);
            WOLF_sprite2.move(0, 10);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            WOLF_sprite.setRotation(90);
            view2.move(10, 0);
            WOLF_sprite.move(10, 0);
            WOLF_sprite2.move(10, 0);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            WOLF_sprite.setRotation(0);
            view2.move(0, -10);
            WOLF_sprite.move(0, -10);
            WOLF_sprite2.move(0, -10);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            WOLF_sprite.setRotation(270);
            view2.move(-10, 0);
            WOLF_sprite.move(-10, 0);
            WOLF_sprite2.move(-10, 0);
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

