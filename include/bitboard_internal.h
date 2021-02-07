#ifndef BITBOARD_INTERNAL_H
#define BITBOARD_INTERNAL_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <string>                            // string
#include <sstream>                           // ostringstream

namespace mp = boost::multiprecision;

namespace bitboard
{
  namespace internal
  {
    std::string uint256tobitstr(mp::uint256_t bigint);
    mp::uint256_t bitstrtouint256(const std::string& str);
  }
}

#endif
