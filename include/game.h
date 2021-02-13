#ifndef GAME_H
#define GAME_H

#include "../include/board.h"
#include "../include/piece.h"
#include <ostream>             // ostream
#include <memory>              // unique_ptr

//template<Element TAgent>
template<typename TAgent>
class Game
{
  public:
    Game(TAgent agent, Board board, std::ostream& os);
    void play();
    
  private:
    TAgent agent;
    Board board;
    std::ostream& os;
    std::unique_ptr<Piece> curpiece;
    std::unique_ptr<Piece> nexpiece;

    bool terminal;
    int level;

    void render();
    void move();
    bool fall();
    bool enqueue();  
};

#endif  // GAME_H
