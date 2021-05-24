#ifndef LOCK_GAME_H
#define LOCK_GAME_H

#include "board.h"
#include "graph.h"
#include "game.h"
#include <ostream>             // ostream
#include <utility>             // pair
#include <memory>              // unique_ptr

// MVC: game interfaces between agent, board, graph, ostream
// game  -- (board, piece)        --> agent
// agent -- (action)              --> game
// game  -- (piece state, action) --> graph 
// graph -- (piece after_state)   --> game
// game  -- (piece after_state)   --> board 
// board -- (board after_state)   --> game
// game  -- (board state)         --> os

class LockGame : public Game<TLockAgent>
{
public:
  Game(TAgent& agent, Board& board, Graph& graph, std::ostream& os);
  void play();
  
protected:
  TAgent& agent;
  Board& board;
  Graph& graph;
  std::ostream& os;
  
  std::pair<uint256_t, int> piece;  // (state, id)
  std::pair<uint256_t, int> next_piece;

  bool terminal;
  int lines;

  virtual void render();  // inherited by graphics game template
  bool move();
  bool enqueue();  
};

#endif  // LOCK_GAME_H
