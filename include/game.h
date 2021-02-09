#ifndef GAME_H
#define

#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"

class Game
{
  public:
    Game();
    
  private:
    Agent agent;
    Board board;
    Piece curpiece;
    Piece nexpiece;
}


#endif
