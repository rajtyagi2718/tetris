#include "../include/bitboard.h"  // bitboard
#include <gtest/gtest.h>          // TEST EXPECT_TRUE
#include <sstream>                // ostringstream
#include <iostream>

TEST(BitBoardTest, Throw)
{
  std::ostringstream oss{};
  bitboard::utils::print(oss, bitboard::bigints::ipiece0);
  EXPECT_TRUE(true) << oss.str();
}
