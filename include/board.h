#ifndef BOARD_H
#define BOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream

namespace mp = boost::multiprecision;

class Board
{
  public:
    Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& board);

  private:
    mp::uint256_t bigint;
};

#endif
