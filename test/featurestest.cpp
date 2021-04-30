#include "../include/features.h" 
#include "../include/bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <gtest/gtest.h>                     // 
#include <iostream>                          // cout endl
#include <sstream>                           // ostringstream
#include <tuple>                  // tuple get
#include <random>                            // random_device mt19937 bernoulli_distribution uniform_int_distribution

namespace boardtest
{
using boost::multiprecision::uint256_t;
using ::testing::TestWithParam;

class Features
{
protected:
  FeatureBase(uint256_t boardint, int expected)
    : boardint{boardint}, expected{expected}, msg{}
  {}

  uint256_t boardint;
  int expected;
  std::ostringstream msg;
  
  virtual int feature() = 0;

  void test()
  {
    ASSERT_EQ(expected, feature())
  }
}

class Clears
  : public TestWithParam<std::tuple<uint256_t, int>>,
    public FeatureBase
{
protected:
  Clears() : FeatureBase{std::get<0>(GetParam()), std::get<1>(GetParam())} {}

  int feature() { return features::clears(boardint); }
};

TEST_P(Clears, HardCoded)
{
  bitboard::print(msg, boardint);
  test()
}

std::tuple<uint256_t> boardints
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
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1})
};

std::tuple<int> expected_clears {0};

INSTANTIATE_TEST_CASE_P(FeatureTest, Clears,
  
  );
}  // namespace boardtest
