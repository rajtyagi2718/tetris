#include "../include/searchgame.h"  // SearchGame
#include "../include/board.h"       // Board
#include "../include/piece.h"       // Piece
#include "../include/agent.h"       // Action
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                   // vector
#include <utility>                  // move
#include <memory>                   // unique_ptr
#include <cassert>                  // assert

using boost::multiprecision::uint256_t; 

SearchGame::SearchGame()
  : board{}, piece{}
{
}

SearchGame::SearchGame(const SearchGame& searchgame)
  : board{searchgame.board}
{
  this->piece = searchgame.piece == nullptr ? 
                nullptr : spawnpieceid(searchgame.piece->getid());
}

void SearchGame::reset(uint256_t boardint, int pieceid)
{
  board.reset(boardint);
  piece = spawnpieceid(pieceid);
}

void SearchGame::search(std::vector<int>& actions)
{
  actions.push_back(1);
  actions.push_back(2);
  actions.push_back(3);
  actions.push_back(4);
}
