#include "../include/bitboard_internal.h"    // bitboard
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <boost/range/adaptor/reversed.hpp>  // reverse
#include <string>                            // string
#include <sstream>                           // ostringstream

namespace mp = boost::multiprecision;
namespace ba = boost::adaptors;

namespace bitboard
{
  namespace internal
  { 
    std::string uint256tobitstr(mp::uint256_t bigint)
    {
      std::ostringstream oss {};
      while (bigint)
      {
        oss << (bigint & 1) ? '1' : '0';
        bigint >>= 1;
      }
    
      return oss.str();
    } 
  
    mp::uint256_t bitstrtouint256(const std::string& bitstr)
    {
      mp::uint256_t res{0};
      for (auto& bitchr : ba::reverse(bitstr))
      {
        // last '1' of bitstr = most significant bit of int
        res <<= 1;
        if (bitchr == '1')
        {
          res += 1;
        }
      }
    
      return res;
    }
  }
}
