#include "../include/searchgame.h"  // SearchGame
#include "../include/board.h"       // Board
#include "../include/piece.h"       // Piece
#include "../include/agent.h"       // Action
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                   // vector
#include <utility>                  // pair
#include <algorithm>                // copy
#include <iterator>                 // back_inserter
#include <memory>                   // unique_ptr
#include <cassert>                  // assert

#include "../include/bitboard.h"
#include <iostream>
#include <sstream>
#include <string>

using boost::multiprecision::uint256_t; 

SearchGame::SearchGame()
  : board{}, piece{}, paths{}
{
}

SearchGame::SearchGame(const SearchGame& searchgame)
  : board{searchgame.board}
{
  this->piece = searchgame.piece ? 
                nullptr : spawnpieceid(searchgame.piece->getid());
}

void SearchGame::reset(uint256_t boardint, int pieceid)
{
  board.reset(boardint);
  piece = spawnpieceid(pieceid);
  for (int i = 0; i < 17; i++) { fall(); }
  std::cout << board << std::endl;
}

// 5**20 nodes => too large for memory. track path

void SearchGame::bestactions(std::vector<int>& actions)
{
  assert(!paths.empty());
  std::copy(paths[0].cbegin(), paths[0].cend(), std::back_inserter(actions));
}

void SearchGame::search()
{
  std::vector<int> path {};
  std::vector<std::pair<int, int>> stack;

  for (auto action : legalactions())
  {
    stack.push_back({0, action});
  }

  while (!stack.empty())
  {
    auto [count, action] = stack.back();
    stack.pop_back();

    while (path.size() > count)
    {
      rise();
      undo(path.back()); 
      path.pop_back();
    } 

    assert(move(action));
    if (!fall())
    {
      paths.push_back(path);
      undo(action); 
      continue;
    }
    path.push_back(action);
    ++count;

    for (auto action : legalactions())
    {
      stack.push_back({count, action});
    }
  }
}

std::vector<int> SearchGame::legalactions()
{
  std::vector<int> ret;
  for (int action = 0; action < Action_END; action++)
  {
    if (move(action))
    {
      ret.push_back(action);
      undo(action);
    }
  }
  return ret;
}

bool SearchGame::move(int action)
{
  board.rempiece(piece->getbigint()); 
  forward(action);

  if (board.trypiece(piece->getbigint()))
  {
    return true;
  }

  backward(action);
  board.addpiece(piece->getbigint());
  return false;
}

void SearchGame::undo(int action)
{
  board.rempiece(piece->getbigint()); 
  backward(action);
  board.addpiece(piece->getbigint());
}

void SearchGame::forward(int action)
{
  switch (action)
  {
    case null:                               break;
    case rotateleft:  piece->rotateleft();   break;
    case left:        piece->left();         break;
    case right:       piece->right();        break;
    case rotateright: piece->rotateright();  break;
  }
}

void SearchGame::backward(int action)
{
  if (action)
  {
    forward(Action_END - action); 
  }
}

bool SearchGame::fall()
{
  board.rempiece(piece->getbigint());
  piece->printrotations(std::cout);
  piece->down();
  if (board.trypiece(piece->getbigint()))
  {
    return true;
  }

  piece->up();
  board.addpiece(piece->getbigint());
  return false;
}

void SearchGame::rise()
{
  board.rempiece(piece->getbigint());
  piece->up();
  board.addpiece(piece->getbigint());
}
