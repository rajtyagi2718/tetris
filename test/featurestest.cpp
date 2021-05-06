#include "../include/features.h" 
#include "../include/bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>                     // 
#include <iostream>                          // cout endl
#include <sstream>                           // ostringstream
#include <vector>

namespace featurestest
{
using boost::multiprecision::uint256_t;

std::vector<uint256_t> boardints
{
bitboard::internal::bitvectouint256(
  {1, 1, 1,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}),

bitboard::internal::bitvectouint256(
  {1, 1, 1,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0,
   1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1})
};

std::vector<int> expected_clears {0, 3};
std::vector<int> expected_heights {0, 50};
std::vector<int> expected_bumps {0, 14};
std::vector<int> expected_holes {0, 4};

TEST(Clears, HardCoded)
{
  auto it = boardints.cbegin();
  auto jt = expected_clears.cbegin();
  while (it != boardints.cend())
  {
    EXPECT_EQ(features::clears(*it), *jt);
    it++;
    jt++;
  } 
}

TEST(Height, HardCoded)
{
  auto it = boardints.cbegin();
  auto jt = expected_heights.cbegin();
  while (it != boardints.cend())
  {
    EXPECT_EQ(features::height(*it), *jt);
    it++;
    jt++;
  } 
}

TEST(Bumps, HardCoded)
{
  auto it = boardints.cbegin();
  auto jt = expected_bumps.cbegin();
  while (it != boardints.cend())
  {
    EXPECT_EQ(features::bumps(*it), *jt);
    it++;
    jt++;
  } 
}

TEST(Holes, HardCoded)
{
  auto it = boardints.cbegin();
  auto jt = expected_holes.cbegin();
  while (it != boardints.cend())
  {
    EXPECT_EQ(features::holes(*it), *jt);
    it++;
    jt++;
  } 
}
}  // namespace featurestest
