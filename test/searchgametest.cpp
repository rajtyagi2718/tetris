#include "../include/searchgame.h"  // SearchGame
#include "../include/bitboard.h"    // board
#include <gtest/gtest.h>        // 
#include <iostream>             // cout endl
#include <sstream>              // ostringstream

namespace searchgametest
{
TEST(SearchGameTest, Constructor)
{
  SearchGame searchgame {};
}

TEST(SearchGameTest, Reset)
{
  SearchGame searchgame {};
  searchgame.reset(bitboard::board, 0); 
}
}  // namespace searchgametest
