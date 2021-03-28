#include "../include/searchgame.h"  // SearchGame
#include "../include/bitboard.h"    // board
#include <gtest/gtest.h>        // 
#include <iostream>             // cout endl
#include <sstream>              // ostringstream

namespace searchgametest
{
TEST(SearchGameTest, Search)
{
  SearchGame searchgame {};
  searchgame.reset(bitboard::board, 0); 
  searchgame.search(); 
}
}  // namespace searchgametest
