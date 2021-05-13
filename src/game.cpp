#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/graph.h"
#include <ostream>                 // ostream
#include <utility>                 // move
#include <cassert>                 // assert

#include <iostream>

template<typename TAgent> Game<TAgent>::Game(
  TAgent& agent, Board& board, Graph& graph, std::ostream& os)
  : agent{agent}, board{board}, graph{graph}, os{os}, 
    piece{}, next_piece{graph.spawn()}, terminal{false}, lines{0}
{
  os << "GAME STARTED" << '\n';
}

template<typename TAgent>
void Game<TAgent>::play()
{
  if (!enqueue())
  {
    terminal = true;
  }
  render();

  while (!terminal)
  {
    if (!move() && !fall())
    {
      lines += board.clear_lines();
      if (!enqueue())
      {
        terminal = true;
      }
    }
    render(); 
  }
  std::cout << "lines: " << lines << std::endl;
}

template<typename TAgent>
void Game<TAgent>::render()
{
  static int count = 0;
  ++count;
  os << "render: " << count << '\n';
  os << board << '\n';
}

template<typename TAgent>
bool Game<TAgent>::move()
{
  int action = agent.act(board.get_state(), piece, next_piece);
  assert(action < Action_END && "agent action out of range [0, 4]");
  board.remove(piece.first); 
  // std::cout << "move" << std::endl;
  graph.move(piece, action); 
  if (board.try_add(piece.first))
  {
    os << "action " << action << '\n';
    return true;
  }
  // std::cout << "undo" << std::endl;
  graph.undo(piece, action); 
  board.add(piece.first);
  return false;
}

template<typename TAgent>
bool Game<TAgent>::fall()
{
  board.remove(piece.first); 
  // std::cout << "fall" << std::endl;
  graph.move(piece, 0); 
  if (board.try_add(piece.first))
  {
    return true;
  }
  // std::cout << "up" << std::endl;
  graph.undo(piece, 0); 
  board.add(piece.first);
  return false;
}

template<typename TAgent>
bool Game<TAgent>::enqueue()
{
  // std::cout << "enqueue piece" << std::endl;
  piece = std::move(next_piece); 
  std::cout << "piece " << piece.second << std::endl;
  if (board.try_add(piece.first))
  {
    next_piece = graph.spawn();
    return true;
  }
  return false; 
}

template class Game<RandomAgent>;
template class Game<SearchAgent>;
