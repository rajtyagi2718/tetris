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
GraphicsGame<TAgent>::GraphicsGame(TAgent& agent, Board board, std::ostream& os)
  : Game<TAgent>{agent, board, os},
    bitmap{sf::Vector2i(32, 32), 11, 23},
    window{sf::VideoMode(352, 736), "tetris"},
    rendertime{sf::seconds(0.01111111f)}
    // rendertime{sf::seconds(0.01666666f)}
    // rendertime{sf::seconds(0.03333333f)}
    // rendertime{sf::seconds(0.11111111f)}
{
}

template<typename TAgent>
void GraphicsGame<TAgent>::render()
{
  static int counter = 0;
  counter++;
  // os << "render: " << counter << '\t';
  bitmap.load(bitboard::uint256tobitvec(board.getbigint()));
  window.clear();
  window.draw(bitmap);
  window.display();
  sf::sleep(rendertime);
}

template class GraphicsGame<RandomAgent>;
template class GraphicsGame<SearchAgent>;
