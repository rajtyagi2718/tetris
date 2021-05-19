#ifndef GRAPHICSGAME_H
#define GRAPHICSGAME_H

#include "board.h"
#include "game.h"
#include "graph.h"
#include "graphics.h"  // Bitmap
#include <SFML/Graphics.hpp>      // sf::RenderWindow sf::Time

//template<Element TAgent>
template<typename TAgent>
class GraphicsGame : public Game<TAgent>
{
public:
  GraphicsGame(TAgent& agent, Board& board, Graph& graph, std::ostream& os);
  using Game<TAgent>::play;
  
private:
  Bitmap bitmap;
  sf::RenderWindow window;
  sf::Time rendertime;
  void render();

  using Game<TAgent>::board;
  using Game<TAgent>::graph;
  using Game<TAgent>::os;
};

#endif  // GRAPHICSGAME_H
