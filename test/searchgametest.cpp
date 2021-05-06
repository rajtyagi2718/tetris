#include "../include/searchgame.h"  // SearchGame
#include "../include/bitboard.h"    // board
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>        // 
#include <utility>              // pair
#include <iostream>             // cout endl
#include <sstream>              // ostringstream
#include <vector>               // vector

namespace searchgametest
{
using boost::multiprecision::uint256_t; 

TEST(SearchGameTest, Search)
{
  SearchGame searchgame {};
  std::vector<std::pair<uint256_t, int>> actions {};
  searchgame.search(bitboard::board, 0, 1, actions); 
  std::cout << "num actions " << actions.size() << std::endl;
  for (auto x : actions) { std::cout << x.second << ' '; } std::cout << std::endl;
}
}  // namespace searchgametest
