#include "../include/bitboard.h"             // bitboard
#include "../include/bitboard_internal.h"    // bitboard
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <boost/range/adaptor/reversed.hpp>  // reverse
#include <ostream>                           // ostream 
#include <string>                            // string

namespace mp = boost::multiprecision;
namespace ba = boost::adaptors;

namespace bitboard
{
  namespace utils
  {
    const int width = 11;

    std::ostream& print(std::ostream& os, mp::uint256_t bigint)
    {
      std::string bitstr{internal::uint256tobitstr(bigint)};
      for (int i = 0; i < bitstr.size(); i += width)
      {
        os << bitstr.substr(i, width) << '\n';
      }
    
      return os; 
    }
  }

  namespace bigints
  {
    const mp::uint256_t   board{internal::bitstrtouint256("10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "10000000000"
                                                          "11111111111")};

    const mp::uint256_t    line{internal::bitstrtouint256("11111111111")};

    const mp::uint256_t ipiece0{internal::bitstrtouint256("00000000000"
                                                          "00001111000")}; 

    const mp::uint256_t ipiece1{internal::bitstrtouint256("00000010000"
                                                          "00000010000"
                                                          "00000010000"
                                                          "00000010000")};                             

    const mp::uint256_t ipiece2{internal::bitstrtouint256("00000000000"
                                                          "00000000000"
                                                          "00000000000"
                                                          "00001111000")}; 

    const mp::uint256_t ipiece3{internal::bitstrtouint256("00000100000"
                                                          "00000100000"
                                                          "00000100000"
                                                          "00000100000")}; 

    const mp::uint256_t  opiece{internal::bitstrtouint256("00000110000"
                                                          "00000110000")}; 

    const mp::uint256_t tpiece0{internal::bitstrtouint256("00000100000"
                                                          "00001110000")}; 

    const mp::uint256_t tpiece1{internal::bitstrtouint256("00000100000"
                                                          "00000110000"
                                                          "00000100000")}; 

    const mp::uint256_t tpiece2{internal::bitstrtouint256("00000000000"
                                                          "00001110000"
                                                          "00000100000")}; 

    const mp::uint256_t tpiece3{internal::bitstrtouint256("00000100000"
                                                          "00001100000"
                                                          "00000100000")}; 

    const mp::uint256_t jpiece0{internal::bitstrtouint256("00001000000"
                                                          "00001110000"
                                                          "00000000000")}; 

    const mp::uint256_t jpiece1{internal::bitstrtouint256("00000110000"
                                                          "00000100000"
                                                          "00000100000")}; 

    const mp::uint256_t jpiece2{internal::bitstrtouint256("00000000000"
                                                          "00001110000"
                                                          "00000010000")}; 

    const mp::uint256_t jpiece3{internal::bitstrtouint256("00000100000"
                                                          "00000100000"
                                                          "00001100000")}; 

    const mp::uint256_t lpiece0{internal::bitstrtouint256("00000010000"
                                                          "00001110000"
                                                          "00000000000")}; 

    const mp::uint256_t lpiece1{internal::bitstrtouint256("00000100000"
                                                          "00000100000"
                                                          "00000110000")}; 

    const mp::uint256_t lpiece2{internal::bitstrtouint256("00000000000"
                                                          "00001110000"
                                                          "00001000000")}; 

    const mp::uint256_t lpiece3{internal::bitstrtouint256("00001100000"
                                                          "00000100000"
                                                          "00000100000")}; 

    const mp::uint256_t zpiece0{internal::bitstrtouint256("00001100000"
                                                          "00000110000"
                                                          "00000000000")}; 

    const mp::uint256_t zpiece1{internal::bitstrtouint256("00000010000"
                                                          "00000110000"
                                                          "00000100000")}; 

    const mp::uint256_t zpiece2{internal::bitstrtouint256("00000000000"
                                                          "00000110000"
                                                          "00001100000")}; 

    const mp::uint256_t zpiece3{internal::bitstrtouint256("00001000000"
                                                          "00001100000"
                                                          "00000100000")}; 

    const mp::uint256_t spiece0{internal::bitstrtouint256("00000110000"
                                                          "00001100000"
                                                          "00000000000")}; 

    const mp::uint256_t spiece1{internal::bitstrtouint256("00000100000"
                                                          "00000110000"
                                                          "00000010000")}; 

    const mp::uint256_t spiece2{internal::bitstrtouint256("00000000000"
                                                          "00000110000"
                                                          "00001100000")}; 

    const mp::uint256_t spiece3{internal::bitstrtouint256("00001000000"
                                                          "00001100000"
                                                          "00000100000")}; 
  }
}
