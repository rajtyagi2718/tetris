#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <ostream>             // ostream
#include <memory>              // make_unique
#include <utility>             // move

template<typename TAgent>
Game<TAgent>::Game(TAgent agent, Board board, std::ostream& os)
  : agent{agent}, board{board}, os{os}, 
    curpiece{spawnpiece()}, nexpiece{spawnpiece()}, 
    terminal{false}, level{0}
{
}

// TODO nexpiece only after curpiece falls once

template<typename TAgent>
void Game<TAgent>::play()
{
  enqueue();
  render();

  while (!terminal)
  {
    for (int i = 2-level; i > 0; i--)
    {
      move(); 
      render();
    }
    if (!fall() && !enqueue())
    {
      terminal = true;
    }
    render(); 
  }
}

template<typename TAgent>
void Game<TAgent>::render()
{
  static int counter = 10;
  os << board;
  counter--;
  if (!counter)
  {
    terminal = true;
  }
}

template<typename TAgent>
void Game<TAgent>::move()
{
  int action = agent.act(board.getbigint());
  board.rempiece(curpiece->getbigint()); 
  switch (action)
  {
    case null: 
    case rotateright: curpiece->rotateright();    
    case rotateleft: curpiece->rotateleft();    
    case left: curpiece->left();    
    case right: curpiece->right();    
  }

  if (! board.trypiece(curpiece->getbigint()))
  {
    // undo action
    switch (action)
    {
      case null: 
      case rotateright: curpiece->rotateleft();    
      case rotateleft: curpiece->rotateright();    
      case left: curpiece->right();    
      case right: curpiece->left();    
    }
    board.addpiece(curpiece->getbigint());
  }
}


template<typename TAgent>
bool Game<TAgent>::fall()
{
  board.rempiece(curpiece->getbigint());
  curpiece->down();
  if (board.trypiece(curpiece->getbigint()))
  {
    return true;
  }

  curpiece->up();
  board.addpiece(curpiece->getbigint());
  return false;
}

template<typename TAgent>
bool Game<TAgent>::enqueue()
{
  if (!curpiece->top())
  {
    curpiece = std::move(nexpiece); 
    nexpiece = spawnpiece();
    board.addpiece(curpiece->getbigint());
    return true;
  }
  return false; 
}

template class Game<RandomAgent>;
