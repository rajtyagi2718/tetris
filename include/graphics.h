#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>  // Drawable RenderTarget RenderStates Vector2i Vertex
#include <vector>             // vector

class Bitmap : public sf::Drawable
{
public:
  Bitmap(sf::Vector2i tile, int width, int height);
  void load(const std::vector<unsigned char>& bitvec);

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  sf::Vector2i tile;
  int width;
  int height;
  std::vector<sf::Vertex> vertices;
};

#endif  // GRAPHICS_H
