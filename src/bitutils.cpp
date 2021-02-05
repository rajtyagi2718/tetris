#include "../include/bitutils.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <boost/range/adaptor/reversed.hpp>  // reverse
#include <sstream>                           // BITUTILS_H

namespace mp = boost::multiprecision;
namespace ba = boost::adaptors;

namespace BoardStr
{
  std::string getstart()
  {
    std::cout << "getstart" << std::endl;
    //     -10123456789
    return "10000000000"  // -2
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
           "11111111111";
  }

  std::string getline()
  {
    std::cout << "getline" << std::endl;
    return "11111111111";
  }
}

namespace BoardInt
{
  const mp::uint256_t start{bitstrtouint256(BoardStr::getstart())};
  const mp::uint256_t line{bitstrtouint256(BoardStr::getline())};
  const int width = 11;
}

std::string BoardInt::uint256tobitstr(mp::uint256_t bigint)
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

mp::uint256_t BoardInt::bitstrtouint256(const std::string& str)
{
  mp::uint256_t res{0};
  for (const auto chr : ba::reverse(str))
  {
    // last '1' of str = most significant bit of int
    res <<= 1;
    if (chr == '1')
    {
      res += 1;
    }
  }

  return res;
}
