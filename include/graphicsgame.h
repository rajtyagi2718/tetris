#ifndef GRAPHICSGAME_H
#define GRAPHICSGAME_H

#include "../include/graphics.h"  // Bitmap
#include "../include/game.h"      // Game
#include <SFML/Graphics.hpp>      // sf::RenderWindow

//template<Element TAgent>
template<typename TAgent>
class GraphicsGame : public Game<TAgent>
{
public:
  GraphicsGame(TAgent& agent, Board board, std::ostream& os);
  using Game<TAgent>::play;
  
private:
  Bitmap bitmap;
  sf::RenderWindow window;
  sf::Time rendertime;
  void render();

  // using Game<TAgent>::Game;
  // using Game<TAgent>::agent;
  using Game<TAgent>::board;
  using Game<TAgent>::os;
  // using Game<TAgent>::curpiece;
  // using Game<TAgent>::nexpiece;
  // using Game<TAgent>::terminal;
  // using Game<TAgent>::lines;
  // using Game<TAgent>::move;
  // using Game<TAgent>::forward;
  // using Game<TAgent>::backward;
  // using Game<TAgent>::fall;
  // using Game<TAgent>::enqueue;  
};

#endif  // GRAPHICSGAME_H
