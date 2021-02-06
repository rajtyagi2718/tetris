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
  namespace bigints
  {
    const mp::uint256_t board{utils::bitstrtouint256(bitstrs::board)};
    const mp::uint256_t line{utils::bitstrtouint256(bitstrs::line)};

    const mp::uint256_t ipiece0{utils::bitstrtouint256(bitstrs::ipiece0)}; 
    const mp::uint256_t opiece0{utils::bitstrtouint256(bitstrs::opiece0)}; 
    const mp::uint256_t tpiece0{utils::bitstrtouint256(bitstrs::tpiece0)}; 
    const mp::uint256_t jpiece0{utils::bitstrtouint256(bitstrs::jpiece0)}; 
    const mp::uint256_t lpiece0{utils::bitstrtouint256(bitstrs::lpiece0)}; 
    const mp::uint256_t zpiece0{utils::bitstrtouint256(bitstrs::zpiece0)}; 
    const mp::uint256_t spiece0{utils::bitstrtouint256(bitstrs::spiece0)}; 
  }

  namespace utils
  {
    const int width = 11;

    std::ostream& print(std::ostream& os, mp::uint256_t bigint)
    {
      std::string bitstr{uint256tobitstr(bigint)};
      for (int i = 0; i < bitstr.size(); i += width)
      {
        os << bitstr.substr(i, width) << '\n';
      }
    
      return os; 
    }
  }
}

