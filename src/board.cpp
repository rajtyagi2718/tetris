#include "../include/board.h"                // Board
#include "../include/bitutils.h"             // BoardInt
#include "../include/exception.h"            // BoardException
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>                          // ostream
#include <string>

Board::Board()
  : bigint{BoardInt::start}
{
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
  std::string bitstr{BoardInt::uint256tobitstr(board.bigint)};
  for (int i = 0; i < bitstr.size(); i += BoardInt::width)
  {
    os << bitstr.substr(i, BoardInt::width) << '\n';
  }

  return os; 
}
