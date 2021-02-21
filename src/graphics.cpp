#include "../include/graphics.h"  // Bitmap
#include <SFML/Graphics.hpp>
#include <iostream>

Bitmap::Bitmap(sf::Vector2i tile, int width, int height)
  : tile{tile}, width{width}, height{height}, 
    vertices(sf::Quads, width*height*4)
{
  // set quad position, color black
  for (int i = 0; i < width; ++i)
  {
    for (int j = 0; j < height; ++j)
    {
      sf::Vertex* quad = &vertices[(i + j * width) * 4];

      quad[0].position = sf::Vector2f(i * tile.x, j * tile.y);
      quad[1].position = sf::Vector2f((i+1) * tile.x, j * tile.y);
      quad[2].position = sf::Vector2f((i+1) * tile.x, (j+1) * tile.y);
      quad[3].position = sf::Vector2f(i * tile.x, (j+1) * tile.y);

      for (int k = 0; k < 4; k++)
      {
        quad[k].color = sf::Color::Black;
      }
    }
  }
}

void Bitmap::load(const std::vector<unsigned char>& bitvec)
{
  for (int i = 0; i < width; ++i)
  {
    for (int j = 0; j < height; ++j)
    {
      sf::Vertex* quad = &vertices[(i + j*width) * 4];

      // bitvec reversed
      sf::Color color {bitvec[width*height-1 - (i + j*width)] ? sf::Color::White : sf::Color::Black};
      for (int k = 0; k < 4; k++)
      {
        quad[k].color = color;
      }
    }
  }
}

void Bitmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(vertices, states);
}
/*
int main()
{
  sf::RenderWindow window{sf::VideoMode(352, 736), "tetris"};

  const std::vector<int> bitvec
  {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3,
    3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3,
    3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1,
    1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1,
    1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1,
    1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0,
    0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0,
    0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
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
*/
