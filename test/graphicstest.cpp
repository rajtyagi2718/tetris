#include "../include/graphics.h"  // Bitmap
#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>

TEST(GraphicsTest, RenderWindow)
{
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

  sf::RenderWindow window{sf::VideoMode(352, 736), "tetris"};
  window.clear();
  window.draw(bitmap);
  window.display();
  sf::sleep(sf::seconds(2));
  window.close();
}
