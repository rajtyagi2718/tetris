#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

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
  sf::VertexArray vertices;
};

#endif  // GRAPHICS_H
