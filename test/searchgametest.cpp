#include "../include/searchgame.h"  // SearchGame
#include "../include/bitboard.h"    // board
#include <gtest/gtest.h>        // 
#include <iostream>             // cout endl
#include <sstream>              // ostringstream
#include <vector>               // vector

namespace searchgametest
{
TEST(SearchGameTest, Search)
{
  SearchGame searchgame {};
  searchgame.reset(bitboard::board, 0); 
  searchgame.search(); 
  std::vector<int> actions {};
  searchgame.bestactions(actions);
  std::cout << "num actions " << actions.size() << std::endl;
  for (auto x : actions) { std::cout << x << ' '; } std::cout << std::endl;
}
}  // namespace searchgametest
