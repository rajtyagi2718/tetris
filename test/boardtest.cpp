#include "../include/board.h"                // 
#include "../include/bitboard.h"             // 
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>                     // 
#include <iostream>                          // cout endl
#include <sstream>                           // ostringstream
#include <random>                            // random_device mt19937 bernoulli_distribution uniform_int_distribution

namespace boardtest
{
using boost::multiprecision::uint256_t;
using bitboard::width;
using bitboard::length;

class ClearLines : public ::testing::TestWithParam<int>
{
protected:
  ClearLines() : board_actual{}, board_expected{}, 
                 gen{rd()}, bdistr{.25}, udistr{1, length},
                 line_actual{bitboard::line}, bit_expected{1}, bit_actual{1},
                 msg{}
  {
    // last line in field of play 
    line_actual  <<= width * (length-2);
    // first three bits are out of range in bitboard
    bit_expected <<= 3 + (width * (length-1)) - 1;
    bit_actual   <<= 3 + (width * (length-1)) - 1;
  }

  Board board_actual;
  Board board_expected;

  std::random_device rd; 
  std::mt19937 gen;
  std::bernoulli_distribution bdistr;
  std::uniform_int_distribution<> udistr;

  uint256_t line_actual;
  uint256_t bit_expected;
  uint256_t bit_actual;

  std::ostringstream msg;
};

TEST_P(ClearLines, BernoulliTrials)
{
  for (int row_actual = length-2; row_actual >= 0; row_actual--)
  {
    if (bdistr(gen))  // fill row
    {
      board_actual.addpiece(line_actual);
      bit_actual >>= width;
    }
    else  // fill bits randomly, except one random bit
    {
      int col_off = udistr(gen);
      for (int col = width-1; col >= 1; col--)
      {
        if (bdistr(gen) && (col_off != col))
        {
          board_expected.addpiece(bit_expected);
          board_actual.addpiece(bit_actual);
        }
        bit_expected >>= 1;
        bit_actual >>= 1;
      }
      bit_expected >>= 1;
      bit_actual >>= 1;
    }
    line_actual >>= width;
  } 

  msg << "board filled\n" << board_actual
      << "board expected\n" << board_expected;
  board_actual.clearlines();
  msg << "board actual\n" << board_actual;
  ASSERT_EQ(board_expected.getbigint(), board_actual.getbigint()) << msg.str();
}

INSTANTIATE_TEST_CASE_P(BoardTest, ClearLines, ::testing::Range(0, 1000));
}  // namespace boardtest
