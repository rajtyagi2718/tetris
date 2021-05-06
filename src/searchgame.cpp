#include "../include/searchgame.h"  // SearchGame
#include "../include/board.h"       // Board
#include "../include/piece.h"       // Piece
#include "../include/agent.h"       // Action
#include "../include/features.h"    // values
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                   // vector
#include <utility>                  // pair
#include <algorithm>                // copy max_element
#include <iterator>                 // back_inserter
#include <memory>                   // unique_ptr
#include <cassert>                  // assert

#include "../include/bitboard.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using boost::multiprecision::uint256_t; 

SearchGame::SearchGame() : board{}, piece{}, weights{}, paths{}, cache{}
{
  std::cout << "search game 1" << std::endl;
  std::ifstream file {"../src/weights.txt"};
  if (file.is_open())
  {
    std::string line;
    std::getline(file, line);
    std::istringstream iss {line};
    double weight;
    while (iss >> weight)
    {
      weights.push_back(weight);
    }
    file.close();
  } 
  else
  {
    assert(false && "cannot open weights.txt file");
  }
}

SearchGame::SearchGame(const SearchGame& searchgame)
  : board{searchgame.board}, weights{searchgame.weights}
{
  std::cout << "search game copy ctr" << std::endl;
  this->piece = searchgame.piece ? 
                spawnpieceid(searchgame.piece->getid()) : nullptr;
}

void SearchGame::search(uint256_t boardint, int curpieceid, int nexpieceid,
                        std::vector<std::pair<uint256_t, int>>& actions)
{
  reset(boardint, curpieceid);
  dfs();

  prepaths = std::move(paths);
  
  for (auto& [prepath, prevalue] : prepaths)
  {
    reset(prepath.back().first, nexpieceid); 
    dfs();
    auto bestpath = std::max_element(paths.cbegin(), paths.cend(),
      [](const auto& x, const auto& y) { return x.second < y.second; });
    prevalue = bestpath->second;
  }

  paths = std::move(prepaths);

  bestactions(actions); 
}

void SearchGame::reset(uint256_t boardint, int pieceid)
{
  board.reset(boardint);
  piece = spawnpieceid(pieceid);
  paths.clear();
  cache.clear();
}

void SearchGame::bestactions(std::vector<std::pair<uint256_t, int>>& actions)
{
  assert(!paths.empty());
  auto path = std::max_element(paths.cbegin(), paths.cend(),
    [](const auto& x, const auto& y) { return x.second < y.second; });
  std::copy(path->first.crbegin(), path->first.crend(),
            std::back_inserter(actions));
  std::cout << "value " << path->second << std::endl;
}

void SearchGame::dfs()
{
  std::vector<std::pair<uint256_t, int>> path {};
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
      undo(path.back().second); 
      assert(board.getbigint() == path.back().first && "backtrack failure");
      path.pop_back();
    } 

    uint256_t state = board.getbigint();
    assert(move(action));
    path.push_back({state, action});
    ++count;

    if (!fall())
    {
      paths.push_back({path, evaluate(board.getbigint())});
      undo(action);
      path.pop_back();
      --count;
      continue;
    }

    for (auto action : legalactions())
    {
      stack.push_back({count, action});
    }
  }
  // std::cout << "num paths " << paths.size() << std::endl;
  // std::cout << "cache size " << cache.size() << std::endl;
}

std::vector<int> SearchGame::legalactions()
{
  std::vector<int> ret;
  for (int action = 0; action < Action_END; action++)
  {
    if (move(action)) 
    {
      if (!cache.count(board.getbigint()))
      {
        ret.push_back(action);
        cache.insert(board.getbigint());
      }
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
  assert(piece->valid() && "forward action invalid");
}

void SearchGame::backward(int action)
{
  if (action)
  {
    forward(Action_END - action); 
  }
  assert(piece->valid() && "backward action invalid");
}

bool SearchGame::fall()
{
  if (piece->last())
  {
    return false;
  }
  board.rempiece(piece->getbigint());
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

double SearchGame::evaluate(uint256_t boardint)
{
  std::vector<double> values = features::values(boardint);
  auto it = weights.cbegin();
  auto jt = values.cbegin();
  double ret = 0.0;
  while (it != weights.cend())
  {
    ret += *it * *jt;
    it++;
    jt++; 
  }
  return ret;
}
