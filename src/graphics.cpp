#include "../include/graphics.h"  // Bitmap
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>                 // vector

Bitmap::Bitmap(sf::Vector2i tile, int width, int height)
  : tile{tile}, width{width}, height{height}, 
    vertices(width*height*4)
{
  // set quad position
  auto qit = vertices.begin();
  for (int j = 0; j < height; ++j)
  {
    for (int i = 0; i < width; ++i)
    {
      for (auto [ii, jj] : {std::pair{0,0}, {1,0}, {1,1}, {0,1}}) 
      {
        (*qit).position = sf::Vector2f((i+ii)*tile.x, (j+jj)*tile.y);
        qit++;
      }
    }
  }
  // set quad color
  for (auto& v: vertices)
  {
    v.color = sf::Color::Black;
  }
}

void Bitmap::load(const std::vector<unsigned char>& bitvec)
{
  // bitvec reversed
  auto bit = bitvec.crbegin();
  auto qit = vertices.begin();
  for (int i = 0; i < width*height; i++)
  {
    sf::Color color {*bit ? sf::Color::White : sf::Color::Black};
    for (int j = 0; j < 4; j++)
    {
      (*qit).color = color;
      qit++;
    }
    bit++;
  }
}

void Bitmap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(vertices.data(), vertices.size(), sf::Quads);
}
