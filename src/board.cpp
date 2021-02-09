#include "../include/board.h"                // Board
#include "../include/bitboard.h"             // print
#include "../include/bitboard_internal.h"             // print
#include "../include/exception.h"            // 
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <string>                            // string
#include <iostream>

Board::Board()
  : bigint{bitboard::bigints::board}
{
}

mp::uint256_t Board::getbigint()
{
  std::cout << "board getter" << std::endl;
  return bigint;
}

const mp::uint256_t& Board::getbigint() const
{
  std::cout << "board const getter" << std::endl;
  return bigint;
}
std::ostream& operator<<(std::ostream& os, const Board& board)
{
  return bitboard::utils::print(os, board.bigint);
}

bool Board::checkpiece(const mp::uint256_t& piece)
{
  return !(bigint & piece);
}

void Board::addpiece(const mp::uint256_t& piece)
{
  bigint |= piece; 
}

bool Board::trypiece(const mp::uint256_t& piece)
{
  if (!(bigint & piece))
  {
    bigint |= piece;
    return true;
  }

  return false;
}

void Board::rempiece(const mp::uint256_t& piece)
{
  bigint &= ~piece;
}

void Board::clearlines()
{
  // TODO fast check any lines full
  // TODO only check lines within piece range 
  int width = bitboard::utils::width;
  mp::uint256_t line{bitboard::bigints::line}; 
  mp::uint256_t upper{bitboard::bigints::line};
  line <<= width; 
  upper |= line;
  line <<= width; 

  // line = "00000000000"    upper = "11111111111"
  //        "00000000000"            "11111111111"
  //        "11111111111"

  for (int i = 0; i < 20; i++)
  {
    if ((bigint & line) == line)
    {
      // above board shifted down union below board
      bigint = ((bigint & upper) << width) | (bigint & ~line & ~upper);
    }
    upper |= line;
    line <<= width;
  }

  bigint |= bitboard::bigints::board; 
}
