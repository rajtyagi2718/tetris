#include "../include/bitboard.h" // bitboard
#include <gtest/gtest.h>         // TEST EXPECT_TRUE
#include <iostream>              // cout endl
#include <string>                // string
#include <vector>                // vector
#include <tuple>                 // tuple tie
#include <random>                // random_device mt19937 bernoulli_distribution

namespace bitboardtest
{
using namespace bitboard;

TEST(BitBoardTest, VecToIntBernoulliTrials)
{
  int numtests = 1000;

  std::vector<unsigned char> bitvec(256, 0); 
  uint256_t expected {0};
  uint256_t actual {0};

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::bernoulli_distribution distrib {};  // default prob = .5

  for (int i = 0; i < numtests; i++)
  {
    expected = 0;
    for (int j = 255; j >= 0; j--)  // bigendian
    {
      expected <<= 1;  // multiply by 2
      if (distrib(gen))
      {
        expected += 1;   // add 1
        bitvec[j] = 1;
      }
      else
      {
        bitvec[j] = 0;
      }
    } 

    actual = internal::bitvectouint256(bitvec);
    ASSERT_EQ(actual, expected);
  }
}

TEST(BitBoardTest, PrintBigInts)
{
  for (auto& [name, bigint] : {
    std::make_tuple("board",   uint256_t {board}),
    std::make_tuple("line",    uint256_t {line}),
    std::make_tuple("ipiece0", uint256_t {ipiece0}),
    std::make_tuple("ipiece1", uint256_t {ipiece1}),
    std::make_tuple("ipiece2", uint256_t {ipiece2}),
    std::make_tuple("ipiece3", uint256_t {ipiece3}),
    std::make_tuple("opiece",  uint256_t {opiece}),
    std::make_tuple("tpiece0", uint256_t {tpiece0}),
    std::make_tuple("tpiece1", uint256_t {tpiece1}),
    std::make_tuple("tpiece2", uint256_t {tpiece2}),
    std::make_tuple("tpiece3", uint256_t {tpiece3}),
    std::make_tuple("jpiece0", uint256_t {jpiece0}),
    std::make_tuple("jpiece1", uint256_t {jpiece1}),
    std::make_tuple("jpiece2", uint256_t {jpiece2}),
    std::make_tuple("jpiece3", uint256_t {jpiece3}),
    std::make_tuple("lpiece0", uint256_t {lpiece0}),
    std::make_tuple("lpiece1", uint256_t {lpiece1}),
    std::make_tuple("lpiece2", uint256_t {lpiece2}),
    std::make_tuple("lpiece3", uint256_t {lpiece3}),
    std::make_tuple("zpiece0", uint256_t {zpiece0}),
    std::make_tuple("zpiece1", uint256_t {zpiece1}),
    std::make_tuple("zpiece2", uint256_t {zpiece2}),
    std::make_tuple("zpiece3", uint256_t {zpiece3}),
    std::make_tuple("spiece0", uint256_t {spiece0}),
    std::make_tuple("spiece1", uint256_t {spiece1}),
    std::make_tuple("spiece2", uint256_t {spiece2}),
    std::make_tuple("spiece3", uint256_t {spiece3})})
  {
    std::cout << name << '\n';
    print(std::cout, bigint);
    std::cout << std::endl;
  }
}
} // namespace bitboardtest
