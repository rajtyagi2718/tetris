#ifndef GAME_H
#define GAME_H

#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <memory>              // unique_ptr

namespace game
{
using board::Board;
using piece::Piece;

//template<Element Agent_>
template<typename Agent_>
class Game
{
  public:
    Game(Agent_ agent_, Board board_);
    
  private:
    Agent_ agent_;
    Board board_;
    //Piece curpiece;
    //Piece nexpiece;
};
}  // namespace game

#endif
