#include "../include/features.h"  // features
#include "../include/bitboard.h"  // width length line block
#include <vector>     // vector
#include <algorithm>  // transform
#include <numeric>    // accumulate adjacent_difference
#include <cmath>      // abs

namespace features
{
int clears(uint256_t boardint)
{
  int ret = 0;
  uint256_t line {bitboard::line}; 
  for (int row = 0; row < bitboard::length-1; row++)
  {
    if ((boardint & line) == line)
    {
      ret++;
    }
    line <<= bitboard::width;
  }
  return ret;
}

int height(uint256_t boardint)
{
  heights = getheights(boardint);
  return std::accumulate(heights.cbegin(), heights.cend(), 0);
}

int bumps(uint256_t boardint)
{
  heights = getheights(boardint);
  std::adjacent_difference(heights.begin(), heights.end(), heights.begin());
  std::transform(heights.begin()+1, heights.end(), heights.begin()+1,
                 [](auto& x) { return std::abs(x); });
  return std::accumulate(heights.cbegin()+1, heights.cend(), 0);
}

int holes(uint256_t boardint)
{
}
}  // namespace features

namespace internal
{
using bitboard::width;
using bitboard::offset;

std::vector<int> getheights(uint256_t boardint)
{
  std::vector<int> ret (bitboard::width - 1);
  uint256_t line {bitboard::line};
  uint256_t block {bitboard::block}; 
  line >>= offset + 1;
  block >>= offset;
  boardint >>= offset+1;

  int height = bitboard::length-1;
  while (line)
  {
    uint256_t top = boardint & line; 
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
    boardint >>= width;
    --height;
  }

  return ret;
}
}  // namespace internal
