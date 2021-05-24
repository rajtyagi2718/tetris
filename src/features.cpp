#include "../include/features.h"
#include "../include/bitboard.h"  // width length line block
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>     // vector
#include <algorithm>  // transform
#include <numeric>    // accumulate adjacent_difference
#include <iterator>   // back_inserter
#include <cmath>      // abs

namespace features
{
std::vector<double> values(uint256_t state, int pre_clears)
{
  std::vector<int> heights = internal::get_heights(state);
  std::vector<int> diffs = internal::get_abs_adjacent_difference(heights);

  double clears = get_clears(state) + pre_clears;
  double height = std::accumulate(heights.cbegin(), heights.cend(), 0.0);
  double bumps = std::accumulate(diffs.cbegin()+1, diffs.cend(), 0.0);
  double holes = height - get_blocks(state);

  return {clears, height, bumps, holes};
}

int get_clears(uint256_t& state)
{
  int ret = 0;
  uint256_t line {bitboard::line}; 
  for (int row = 0; row < bitboard::length-1; row++)
  {
    if ((state & line) == line)
    {
      ret++;
    }
    line <<= bitboard::width;
  }
  return ret;
}

int get_blocks(uint256_t& state)
{
  int ret = 0;
  uint256_t block = bitboard::block;

  for (int row = 0; row < bitboard::length-1; row++)
  {
    block <<= 1;
    for (int col = 0; col < bitboard::width-1; col++)
    {
      if (state & block)
      { 
        ++ret;
      }
      block <<= 1;
    }
  }
  return ret;
}
}  // namespace features

namespace internal
{
using bitboard::width;
using bitboard::offset;

std::vector<int> get_heights(uint256_t state)
{
  std::vector<int> ret (bitboard::width - 1);
  uint256_t line {bitboard::line};
  uint256_t block {bitboard::block}; 
  line >>= offset + 1;
  block >>= offset;
  state >>= offset+1;

  int height = bitboard::length-1;
  while (line)
  {
    uint256_t top = state & line; 
    line ^= top;
    int col = 0;
    while (top)
    {
      if (top & block)
      {
        ret[col] = height;
      }
      top >>= 1;
      ++col;
    }
    state >>= width;
    --height;
  }

  return ret;
}

std::vector<int> get_abs_adjacent_difference(std::vector<int>& heights)
{
  std::vector<int> ret {};
  std::adjacent_difference(heights.cbegin(), heights.cend(),
                           std::back_inserter(ret));
  std::transform(ret.begin(), ret.end(), ret.begin(),
                 [](auto& x) { return std::abs(x); });
  return ret;
}
}  // namespace internal
