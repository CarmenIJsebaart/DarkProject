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

  sf::CircleShape RedRidingHood;
  RedRidingHood.setRadius(10.0);
  RedRidingHood.setFillColor(sf::Color::Red);
  RedRidingHood.setPosition(sf::Vector2f(500, 500));

  sf::CircleShape Wolf;
  Wolf.setRadius(10.0);
  Wolf.setFillColor(sf::Color(120, 120, 120));
  Wolf.setPosition(sf::Vector2f(500, 500));

  sf::RectangleShape eraser;
  eraser.setOutlineColor(sf::Color::Yellow);
  eraser.setFillColor(sf::Color::Transparent);
  eraser.setOutlineThickness(2);
  eraser.setSize(sf::Vector2f(w_size_x, w_size_y*2));

  sf::Texture grass;
  grass.loadFromFile("Grass.png");
  sf::Sprite map(grass);

  sf::Texture RRH;
  RRH.loadFromFile("CandlePicture_redhood.png");
  sf::Sprite RRH_sprite(RRH);
  RRH_sprite.setPosition(200, 200);

  sf::Texture WOLF;
  WOLF.loadFromFile("CandlePicture_wolf.png");
  sf::Sprite WOLF_sprite(WOLF);
  WOLF_sprite.setPosition(200, 200);

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
        default:
          break;
      }
    }

    w.clear();

    w.setView(view1);
    w.draw(map);
    w.draw(RRH_sprite);

    w.setView(view2);
    w.draw(map);
    w.draw(WOLF_sprite);

    w.display();
  }
}

