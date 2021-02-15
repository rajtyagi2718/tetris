#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <ostream>                 // ostream
#include <memory>                  // make_unique
#include <utility>                 // move
#include <cassert>                 // assert

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
  board.addpiece(curpiece->getbigint());
  render();

  while (!terminal)
  {
    for (int i = 2; i > 0; i--)
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
  static int counter = -1;
  os << "render counter: " << counter << '\n';
  os << board << '\n';
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
  assert(action < Action_END && "agent action out of range [0, 4]");
  std::cout << "action " << action << std::endl;
  board.rempiece(curpiece->getbigint()); 
  switch (action)
  {
    case null: break;
    case rotateright: curpiece->rotateright();  break;
    case rotateleft:  curpiece->rotateleft();  break;
    case left:        curpiece->left();  break;
    case right:       curpiece->right();  break;
  }

  if (!board.trypiece(curpiece->getbigint()))
  {
    std::cout << "action blocked." << std::endl;
    // undo action
    switch (action)
    {
      case null: break;
      case rotateright: curpiece->rotateleft();  break;
      case rotateleft:  curpiece->rotateright();  break;
      case left:        curpiece->right();  break;
      case right:       curpiece->left();  break;
    }
    board.addpiece(curpiece->getbigint());
  }
  else { std::cout << "action success." << std::endl; }
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
