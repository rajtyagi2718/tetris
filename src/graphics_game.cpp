#include "../include/graphics_game.h"
#include "../include/bitboard.h"
#include "../include/board.h"
#include "../include/graph.h"
#include "../include/agent.h"
#include "../include/game.h"
#include "../include/graphics.h"
#include <ostream>
#include <utility>  // move

template<typename TAgent>
GraphicsGame<TAgent>::GraphicsGame(TAgent& agent, Board& board, Graph& graph, std::ostream& os)
  : Game<TAgent>{agent, board, graph, os},
    bitmap{sf::Vector2i(32, 32), 11, 23},
    window{sf::VideoMode(352, 736), "tetris"},
    rendertime{sf::seconds(0.01111111f)}
    // rendertime{sf::seconds(0.01666666f)}
    // rendertime{sf::seconds(0.03333333f)}
    // rendertime{sf::seconds(0.11111111f)}
    // rendertime{sf::seconds(1)}
{
}

template<typename TAgent>
void GraphicsGame<TAgent>::render()
{
  bitmap.load(bitboard::to_bits(board.get_state()));
  window.clear();
  window.draw(bitmap);
  window.display();
  sf::sleep(rendertime);
}

template class GraphicsGame<RandomAgent>;
template class GraphicsGame<SearchAgent>;
