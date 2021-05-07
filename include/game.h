#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/piece.h"
#include <ostream>             // ostream
#include <memory>              // unique_ptr
#include <vector>

template<typename TAgent>
class Game
{
public:
  Game(TAgent& agent, Board board, std::ostream& os);
  void play();
  
protected:
  TAgent agent;
  Board board;
  std::ostream& os;
  SevenBagRandomizer randomizer;
  std::unique_ptr<Piece> curpiece;
  std::unique_ptr<Piece> nexpiece;

  std::vector<int> pieceids;

  bool terminal;
  int lines;

  virtual void render();
  void move();
  void forward(int action);
  void backward(int action);
  bool fall();
  bool enqueue();  
};

#endif  // GAME_H
