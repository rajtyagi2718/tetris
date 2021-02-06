#include "../include/piece.h"
#include "../include/bitboard.h"  // print
#include <ostream>                // ostream
#include <string>                 // string
#include <vector>                 // vector

Piece::Piece(mp::uint256_t r0, mp::uint256_t r1, mp::uint256_t r2, 
             mp::uint256_t r3)  
  : rot{0}, rotations{r0, r1, r2, r3}
{
}

mp::uint256_t Piece::getbigint() const
{
  return rotations[rot];
}

std::ostream& operator<<(std::ostream& os, Piece& piece)
{
  return bitboard::utils::print(os, piece.getbigint());
}

IPiece::IPiece()
  : Piece(bitboard::bigints::ipiece0, 
          bitboard::bigints::ipiece0, 
          bitboard::bigints::ipiece0,
          bitboard::bigints::ipiece0)
{
}
