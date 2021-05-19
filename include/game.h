#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "graph.h"
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

template<typename TAgent>
class Game
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
  bool fall();
  bool enqueue();  
};

#endif  // GAME_H
