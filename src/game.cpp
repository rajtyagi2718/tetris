#include "../include/game.h"
#include "../include/board.h"
#include "../include/graph.h"
#include "../include/agent.h"
#include "../include/ids.h"    // Action
#include <ostream>
#include <utility>  // move
#include <cassert>  // assert

template<typename TAgent> Game<TAgent>::Game(
  TAgent& agent, Board& board, Graph& graph, std::ostream& os)
  : agent{agent}, board{board}, graph{graph}, os{os}, 
    piece{}, next_piece{graph.spawn()}, terminal{false}, lines{0}
{
}

template<typename TAgent>
void Game<TAgent>::play()
{
  os << "play" << std::endl
     << "agent=" << agent << std::endl;
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
        os << "terminal" << std::endl;
        terminal = true;
      }
    }
    render(); } os << "lines=" << lines << std::endl;
}

template<typename TAgent>
void Game<TAgent>::render()
{
  os << board << std::endl;
}

template<typename TAgent>
bool Game<TAgent>::move()
{
  int action = agent.act(board.get_state(), piece, next_piece);
  assert(action < Action_END && "agent action out of range [0, 4]");
  board.remove(piece.first); 
  graph.move(piece, action); 
  if (board.try_add(piece.first))
  {
    os << "action=" << action << std::endl;
    return true;
  }
  graph.undo(piece, action); 
  board.add(piece.first);
  return false;
}

template<typename TAgent>
bool Game<TAgent>::fall()
{
  board.remove(piece.first); 
  graph.move(piece, 0); 
  if (board.try_add(piece.first))
  {
    os << "fall" << std::endl;
    return true;
  }
  graph.undo(piece, 0); 
  board.add(piece.first);
  return false;
}

template<typename TAgent>
bool Game<TAgent>::enqueue()
{
  piece = std::move(next_piece); 
  os << "enqueue piece: id=" << piece.second << std::endl;
  if (board.try_add(piece.first))
  {
    next_piece = graph.spawn();
    return true;
  }
  return false; 
}

template class Game<RandomAgent>;
template class Game<SearchAgent>;
