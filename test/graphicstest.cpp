#include "../include/graphics.h"  // Bitmap
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

TEST(GraphicsTest, RenderWindow)
{
  sf::RenderWindow window{sf::VideoMode(352, 736), "tetris"};

  const std::vector<unsigned char> bitvec
  {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 
  };

  Bitmap bitmap {sf::Vector2i(32, 32), 11, 23};
  bitmap.load(bitvec);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    window.clear();
    window.draw(bitmap);
    window.display();
  }
}
