#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
  sf::RenderWindow w(sf::VideoMode(600, 600), "DarkProject", sf::Style::Titlebar | sf::Style::Close);

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
    w.display();
  }
}

