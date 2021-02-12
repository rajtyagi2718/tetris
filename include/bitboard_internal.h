#ifndef BITBOARD_INTERNAL_H
#define BITBOARD_INTERNAL_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector
#include <string>                            // string

namespace bitboard
{
  using uint256_t = boost::multiprecision::uint256_t;

  namespace internal
  {
    std::string uint256tobitstr(uint256_t bigint);
    uint256_t bitvectouint256(std::vector<unsigned char> bitvec);
  }
}

#endif
