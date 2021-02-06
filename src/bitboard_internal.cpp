#include "../include/bitboard_internal.h"    // bitboard
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <boost/range/adaptor/reversed.hpp>  // reverse
#include <string>                            // string
#include <sstream>                           // ostringstream

namespace mp = boost::multiprecision;
namespace ba = boost::adaptors;

namespace bitboard
{
  namespace bitstrs
  {
    //                      -10123456789
    const std::string board{"10000000000"  // -2
                            "10000000000"  // -1
                            "10000000000"  //  0
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"  //  9
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"
                            "10000000000"  // 19
                            "11111111111"};
  
    const std::string line{"11111111111"};
  
    const std::string ipiece0{'0'}; 
    const std::string opiece0{'4'}; 
    const std::string tpiece0{'4'}; 
    const std::string jpiece0{'1'}; 
    const std::string lpiece0{'2'}; 
    const std::string zpiece0{'3'}; 
    const std::string spiece0{'5'}; 
  }
 
  namespace utils
  { 
    std::string uint256tobitstr(mp::uint256_t bigint)
    {
      std::ostringstream oss {};
      while (bigint)
      {
        if (bigint & 1)
        {
          oss << '1';
        }
        else
        {
          oss << '0';
        } 
        bigint >>= 1;
      }
    
      return oss.str();
    } 
  
    mp::uint256_t bitstrtouint256(const std::string& bitstr)
    {
      mp::uint256_t res{0};
      for (const auto bitchr : ba::reverse(bitstr))
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
