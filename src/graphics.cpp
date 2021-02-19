#include <SFML/Graphics.hpp>
#include <iostream>

class Bitmap : public sf::Drawable, public sf::Transformable
{
public:
  Bitmap(sf::Vector2u tileSize, unsigned int width, unsigned int height)
  : tileSize{tileSize}, width{width}, height{height}, m_vertices(sf::Quads, width*height*4)
  {}

  bool load(const std::vector<int>& bitvec)
  {
  // resize the vertex array to fit the bitvec size
  // TODO in constructor

  // populate the vertex array, with one quad per tile
  for (unsigned int i = 0; i < width; ++i)
    for (unsigned int j = 0; j < height; ++j)
    {
    // get a pointer to the current tile's quad
    sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

    // define its 4 corners
    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
        quad[1].position = sf::Vector2f((i+1) * tileSize.x, j * tileSize.y);
        quad[2].position = sf::Vector2f((i+1) * tileSize.x, (j+1) * tileSize.y);
        quad[3].position = sf::Vector2f(i * tileSize.x, (j+1) * tileSize.y);

        // define its 4 colors
        sf::Color color {bitvec[i + j*width] ? sf::Color::Black : sf::Color::White};
        for (int i = 0; i < 4; i++)
        {
          quad[i].color = color;
        }
      }

    return true;
  }

private:

  // TODO rm states, transform, only drawable
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the transform
    states.transform *= getTransform();

    // draw the vertex array
    target.draw(m_vertices, states);
  }

  sf::Vector2u tileSize;
  unsigned int width;
  unsigned int height;
  sf::VertexArray m_vertices;
};

int main()
{
  // create the window
  sf::RenderWindow window(sf::VideoMode(352, 736), "tetris");

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

  // create the tilebitmap from the bitvec definition
  Bitmap bitmap {sf::Vector2u(32, 32), 11, 23};
  bitmap.load(bitvec);

  // run the main loop
  while (window.isOpen())
  {
    // handle events
    sf::Event event;
    while (window.pollEvent(event))
    {
      if(event.type == sf::Event::Closed)
        window.close();
    }

    // draw the bitmap
    window.clear();
    window.draw(bitmap);
    window.display();
  }
}
