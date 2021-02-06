#ifndef BITBOARD_H
#define BITBOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t

namespace mp = boost::multiprecision;

namespace bitboard
{
  namespace bigints
  {
    extern const mp::uint256_t board;
    extern const mp::uint256_t line;

    extern const mp::uint256_t ipiece0; 
    extern const mp::uint256_t opiece0; 
    extern const mp::uint256_t tpiece0; 
    extern const mp::uint256_t jpiece0; 
    extern const mp::uint256_t lpiece0; 
    extern const mp::uint256_t zpiece0; 
    extern const mp::uint256_t spiece0; 
  }

  namespace utils
  {
    extern const int width;

    std::ostream& print(std::ostream& os, mp::uint256_t bigint);
  }
}

#endif
