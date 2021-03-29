#include "../include/bitboard.h" // 
#include <gtest/gtest.h>         // 
#include <iostream>              // cout endl
#include <sstream>               // ostringstream
#include <string>                // string
#include <vector>                // vector
#include <tuple>                 // tuple tie
#include <random>                // random_device mt19937 bernoulli_distribution

namespace bitboardtest
{
using boost::multiprecision::uint256_t;
using ::testing::TestWithParam;
using ::testing::Range;
using ::testing::Values;

class VecToInt : public TestWithParam<int>
{
protected:
  VecToInt() : 
    bitvec(256, 0), expected{0}, actual{0}, msg{}, gen{rd()}, distr{} {}

  std::vector<unsigned char> bitvec; 
  uint256_t expected;
  uint256_t actual;
  std::ostringstream msg;

  std::random_device rd; 
  std::mt19937 gen;
  std::bernoulli_distribution distr;  // default prob = .5
};

TEST_P(VecToInt, BernoulliTrials)
{
  // randomly set bits, track expected bigint
  for (int j = 255; j >= 0; j--)  // bigendian
  {
    expected <<= 1;   // multiply by 2
    if (distr(gen))
    {
      expected += 1;  // add 1
      bitvec[j] = 1;
    }
  } 

  // build error message
  for (auto x : bitvec) { msg << x; }

  actual = bitboard::internal::bitvectouint256(bitvec);
  ASSERT_EQ(expected, actual) << msg.str();
}

INSTANTIATE_TEST_CASE_P(BitBoardTest, VecToInt, Range(0, 1000));

class Print : public TestWithParam<std::tuple<std::string, uint256_t>>
{
protected:
  Print() { std::tie(name, bigint) = GetParam(); }
  std::string name;
  uint256_t bigint;
};

TEST_P(Print, BigInts)
{
  std::cout << name << '\n';
  bitboard::print(std::cout, bigint);
  std::cout << std::endl;
}

INSTANTIATE_TEST_CASE_P(BitBoardTest, Print, Values(
    std::make_tuple("board",   uint256_t {bitboard::board}),
    std::make_tuple("line",    uint256_t {bitboard::line}),
    std::make_tuple("tpiece0", uint256_t {bitboard::tpiece0}),
    std::make_tuple("tpiece1", uint256_t {bitboard::tpiece1}),
    std::make_tuple("tpiece2", uint256_t {bitboard::tpiece2}),
    std::make_tuple("tpiece3", uint256_t {bitboard::tpiece3}),
    std::make_tuple("jpiece0", uint256_t {bitboard::jpiece0}),
    std::make_tuple("jpiece1", uint256_t {bitboard::jpiece1}),
    std::make_tuple("jpiece2", uint256_t {bitboard::jpiece2}),
    std::make_tuple("jpiece3", uint256_t {bitboard::jpiece3}),
    std::make_tuple("zpiece0", uint256_t {bitboard::zpiece0}),
    std::make_tuple("zpiece1", uint256_t {bitboard::zpiece1}),
    std::make_tuple("opiece0", uint256_t {bitboard::opiece0}),
    std::make_tuple("spiece0", uint256_t {bitboard::spiece0}),
    std::make_tuple("spiece1", uint256_t {bitboard::spiece1}),
    std::make_tuple("lpiece0", uint256_t {bitboard::lpiece0}),
    std::make_tuple("lpiece1", uint256_t {bitboard::lpiece1}),
    std::make_tuple("lpiece2", uint256_t {bitboard::lpiece2}),
    std::make_tuple("lpiece3", uint256_t {bitboard::lpiece3}),
    std::make_tuple("ipiece0", uint256_t {bitboard::ipiece0}),
    std::make_tuple("ipiece1", uint256_t {bitboard::ipiece1})));
} // namespace bitboardtest
