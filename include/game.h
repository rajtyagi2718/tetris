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
    int lines;

    void render();
    void move();
    void forward(int action);
    void backward(int action);
    bool fall();
    bool enqueue();  
};

#endif  // GAME_H
