#include "../include/board.h"                // Board
#include "../include/bitboard.h"             // print
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <string>                            // string
#include <vector>                            // vector

Board::Board()
  : state{bitboard::board}
{
}

Board::Board(uint256_t state)
  : state{state}
{
}

uint256_t Board::get_state()
{
  return state;
}

const uint256_t& Board::get_state() const
{
  return state;
}

void Board::reset()
{
  this->state = bitboard::board;
}

std::ostream& operator<<(std::ostream& os, const Board& board)
{
  return bitboard::print(os, board.state);
}

bool Board::is_valid(const uint256_t& piece)
{
  return !(state & piece);
}

void Board::add(const uint256_t& piece)
{
  state |= piece; 
}

bool Board::try_add(const uint256_t& piece)
{
  if (!(state & piece))
  {
    state |= piece;
    return true;
  }

  return false;
}

void Board::remove(const uint256_t& piece)
{
  state &= ~piece;
}

int Board::clear_lines()
{
  int count = 0;
  // TODO fast check any lines full
  // TODO only check lines within piece range 
  int  width = bitboard::width;
  int length = bitboard::length;
  uint256_t line{bitboard::line}; 

  if ((state & line) == line)
  {
    // clear top line from board
    state &= ~line;
    count++;
  }

  uint256_t upper{bitboard::line};
  line <<= width; 

  // line = "00000000000"    upper = "11111111111"
  //        "11111111111"

  for (int row = 1; row < length-1; row++)
  {
    if ((state & line) == line)
    {
      // above board shifted down union below board
      state = ((state & upper) << width) | (state & ~line & ~upper);
      count++;
    }
    upper |= line;
    line <<= width;
  }

  state |= bitboard::board; 
  return count;
}
