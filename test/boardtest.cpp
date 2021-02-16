#include "../include/board.h"                // Board
#include "../include/bitboard.h"             // print
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>                     // TEST EXPECT_TRUE
#include <iostream>                          // cout endl
#include <sstream>                           // ostringstream
#include <random>                            // random_device mt19937 bernoulli_distribution

namespace boardtest
{
TEST(BoardTest, ClearLines)
{
  std::ostringstream oss {};
  Board board_actual {};
  Board board_expected {};
  oss << "board start\n" << board_actual;

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::bernoulli_distribution distr {.25};

  int width = bitboard::width;
  uint256_t line = bitboard::line;
  uint256_t bit = 1;
  bit <<= 3; 

  for (int row = 0; row < 23; row++)
  {
    if (distr(gen))
    {
      board_actual.addpiece(line);
      bit <<= width;
    }
    else
    {
      for (int col = 0; col < width; col++)
      {
        if (distr(gen))
        {
          board_actual.addpiece(bit);
          board_expected.addpiece(bit);
        }
        bit <<= 1;
      }
    }
    line <<= width;
  } 

  oss << "board fill\n" << board_actual;
  board_actual.clearlines();
  oss << "board clear\n" << board_actual;

  std::cout << oss.str();

  ASSERT_EQ(board_expected.getbigint(), board_actual.getbigint()) << oss.str();
}

}  // namespace boardtest
