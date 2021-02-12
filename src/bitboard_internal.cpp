#include "../include/bitboard_internal.h"    // bitboard
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t import_bits
#include <boost/range/adaptor/reversed.hpp>  // reverse
#include <vector>                            // vector
#include <string>                            // string
#include <sstream>                           // ostringstream

namespace bitboard
{
  namespace internal
  { 
    std::string uint256tobitstr(uint256_t bigint)
    {
      std::ostringstream oss {};
      while (bigint)
      {
        oss << (bigint & 1) ? '1' : '0';
        bigint >>= 1;
      }
    
      return oss.str();
    } 

    uint256_t bitvectouint256(std::vector<unsigned char> bitvec)
    {
      uint256_t ret;
      // unsigned chunk_size = 1 bit
      // msv_first = false  i.e.  bigendian
      boost::multiprecision::import_bits(
        ret, bitvec.begin(), bitvec.end(), 1, false);
    
      return ret;
    }
  }
}
