#include "../include/board.h"  // Board
#include "../include/bitboard.h"             // print
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>       // TEST EXPECT_TRUE
#include <iostream>            // cout endl

namespace mp = boost::multiprecision;

TEST(BoardTest, Throw)
{
  Board board{};

  std::cout << "board start\n" << board << std::endl;

  int width = bitboard::utils::width;
  mp::uint256_t line{bitboard::bigints::line};
  for (auto i : {3, 2, 1, 2, 1, 1, 4, 1, 1, 1})
  {
    line <<= width * i;
    board.addpiece(line);
  } 
  std::cout << "board fills\n" << board << std::endl;

  board.clearlines();
  std::cout << "board clears\n" << board << std::endl;

  EXPECT_TRUE(true);
}
