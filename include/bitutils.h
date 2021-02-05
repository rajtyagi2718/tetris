#ifndef BITUTILS_H
#define BITUTILS_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t

namespace mp = boost::multiprecision;

// BOARD
// 20x10 play field
// 23x11 bit mask = 253 bits
// int: 0 empty  1 long  2 j  3 l  4 square  5 s  6 t  7 z

namespace BoardInt
{
  extern const mp::uint256_t start;
  extern const mp::uint256_t line;
  extern const int width;

  std::string uint256tobitstr(mp::uint256_t bigint);
  // mp::uint256_t bitstrtouint256(const std::string& str) const
  mp::uint256_t bitstrtouint256(const std::string& str);
}

#endif
