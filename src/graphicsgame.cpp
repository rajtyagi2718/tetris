#include "../include/graphicsgame.h"
#include "../include/graphics.h"
#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include "../include/bitboard.h"
#include <ostream>                 // ostream
#include <utility>                 // move
#include <cassert>                 // assert

template<typename TAgent>
GraphicsGame<TAgent>::GraphicsGame(TAgent agent, Board board, std::ostream& os)
  : Game<TAgent>{agent, board, os},
    bitmap{sf::Vector2i(32, 32), 11, 23},
    window{sf::VideoMode(352, 736), "tetris"},
    renderclock{}, fallclock{}, //rendertime{}, falltime{} 
    rendertime{sf::seconds(0.166667f)}, falltime{sf::seconds(0.8f)}
{
}

template<typename TAgent>
void GraphicsGame<TAgent>::play()
{
  /*
  for (int i = 0; i < 10; i++)
  {
    std::cout << renderclock.getElapsedTime().asMilliseconds() << std::endl;
    std::cout << rendertime.asMilliseconds() << std::endl;
    if (renderclock.getElapsedTime() >= rendertime)
    {
      std::cout << "rendering" << std::endl;
      renderclock.restart();
    }
    sf::sleep(rendertime); 
  }
  return;
  */

  if (!enqueue())
  {
    terminal = true;
  }
  render();

  while (!terminal)
  {
    for (int i = 2; i > 0; i--)
    {
      move(); 
      render();
    }
    if (!fall())
    {
      lines += board.clearlines();
      if (!enqueue())
      {
        terminal = true;
      }
    }
    render(); 
    sf::sleep(rendertime);
  }
  if (lines) { std::cout << "lines: " << lines << std::endl; }
}

template<typename TAgent>
void GraphicsGame<TAgent>::render()
{
  static int counter = 0;
  counter++;
  os << "render: " << counter << '\n';
  os << board << '\n';
  bitmap.load(bitboard::uint256tobitvec(board.getbigint()));
  window.clear();
  window.draw(bitmap);
  window.display();
}

template class GraphicsGame<RandomAgent>;
