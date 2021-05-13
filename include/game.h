#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/graph.h"
#include <ostream>             // ostream
#include <utility>             // pair
#include <memory>              // unique_ptr

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
  
  std::pair<uint256_t, int> piece;
  std::pair<uint256_t, int> next_piece;

  bool terminal;
  int lines;

  virtual void render();
  bool move();
  bool fall();
  bool enqueue();  
};

#endif  // GAME_H
