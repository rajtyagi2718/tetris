#include "../include/bitboard.h" // bitboard
#include <gtest/gtest.h>         // TEST EXPECT_TRUE
#include <sstream>               // ostringstream
#include <iostream>

namespace bitboardtest
{
TEST(BitBoardTest, Throw)
{
  std::ostringstream oss{};
  bitboard::print(oss, bitboard::ipiece0, false);
  EXPECT_TRUE(true) << oss.str();
}
} // namespace bitboardtest
