#ifndef BITBOARD_INTERNAL_H
#define BITBOARD_INTERNAL_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <string>                            // string

// BOARD
// 20x10 play field
// 23x11 bit mask = 253 bits
// int: 0 empty  1 long  2 j  3 l  4 square  5 s  6 t  7 z

namespace mp = boost::multiprecision;

namespace bitboard
{
  namespace bitstrs
  {
    extern const std::string board; 
    extern const std::string line; 
    extern const std::string ipiece0; 
    extern const std::string opiece0; 
    extern const std::string tpiece0; 
    extern const std::string jpiece0; 
    extern const std::string lpiece0; 
    extern const std::string zpiece0; 
    extern const std::string spiece0; 
  }

  namespace utils
  {
    std::string uint256tobitstr(mp::uint256_t bigint);
    mp::uint256_t bitstrtouint256(const std::string& str);
  }
}

#endif
