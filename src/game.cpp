#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <ostream>                 // ostream
#include <utility>                 // move
#include <cassert>                 // assert

template<typename TAgent>
Game<TAgent>::Game(TAgent agent, Board board, std::ostream& os)
  : agent{agent}, board{board}, os{os}, 
    curpiece{}, nexpiece{spawnpiece()}, 
    terminal{false}, level{0}, lines{0}
{
}

// TODO nexpiece only after curpiece falls once

template<typename TAgent>
void Game<TAgent>::play()
{
  if (!enqueue())
  {
    terminal = true;
  }
  render();

  while (!terminal)
  {
    for (int i = 2; i > 0; i--)
    {
      move(); 
      render();
    }
    if (!fall())
    {
      lines += board.clearlines();
      if (!enqueue())
      {
        terminal = true;
      }
    }
    render(); 
  }
  if (lines) { std::cout << "lines: " << lines << std::endl; }
}

template<typename TAgent>
void Game<TAgent>::render()
{
  static int count = -1;
  os << "render: " << count << '\n';
  os << board << '\n';
  count--;
  if (!count)
  {
    terminal = true;
  }
}

template<typename TAgent>
void Game<TAgent>::move()
{
  int action = agent.act(board.getbigint());
  assert(action < Action_END && "agent action out of range [0, 4]");
  board.rempiece(curpiece->getbigint()); 
  forward(action);

  if (!board.trypiece(curpiece->getbigint()))
  {
    backward(action);
    board.addpiece(curpiece->getbigint());
  }
  else { os << "action " << action << '\n'; }
}

template<typename TAgent>
void Game<TAgent>::forward(int action)
{
  switch (action)
  {
    case rotateleft:  curpiece->rotateleft();   break;
    case left:        curpiece->left();         break;
    case null:                                  break;
    case right:       curpiece->right();        break;
    case rotateright: curpiece->rotateright();  break;
  }
}

template<typename TAgent>
void Game<TAgent>::backward(int action)
{
  forward(Action_END-1 - action); 
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
  curpiece = std::move(nexpiece); 
  if (board.trypiece(curpiece->getbigint()))
  {
    nexpiece = spawnpiece();
    return true;
  }
  return false; 
}

template class Game<RandomAgent>;
