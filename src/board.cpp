#include "../include/board.h"                // Board
#include "../include/bitboard.h"             // print
#include "../include/exception.h"            // 
#include <ostream>                           // ostream
#include <string>                            // string

Board::Board()
  : bigint{bitboard::bigints::board}
{
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
  return bitboard::utils::print(os, board.bigint);
}
