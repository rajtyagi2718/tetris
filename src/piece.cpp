#include "../include/piece.h"
#include "../include/bitboard.h"             // print
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <iostream>

namespace mp = boost::multiprecision;

Piece::Piece(mp::uint256_t r0, mp::uint256_t r1, mp::uint256_t r2, 
             mp::uint256_t r3)  
  : rot{0}, rotations{r0, r1, r2, r3}
{
}

Piece::Piece(mp::uint256_t r)  
  : rot{0}, rotations{r}
{
}

mp::uint256_t Piece::getbigint()
{
  std::cout << "piece getter" << std::endl;
  return rotations[rot];
}

const mp::uint256_t& Piece::getbigint() const
{
  std::cout << "piece const getter" << std::endl;
  return rotations[rot];
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
  return bitboard::utils::print(os, piece.getbigint());
}

void Piece::rotateright()
{
  rot = (rot + 1) % 4; 
} 

void Piece::rotateleft()
{
  rot = (rot - 1) % 4; 
} 

void Piece::up()
{
  for (auto& bigint : rotations)
  {
    bigint >>= bitboard::utils::width; 
  }
}

void Piece::down()
{
  for (auto& bigint : rotations)
  {
    bigint <<= bitboard::utils::width; 
  }
}

void Piece::left()
{
  for (auto& bigint : rotations)
  {
    bigint >>= 1; 
  }
}

void Piece::right()
{
  for (auto& bigint : rotations)
  {
    bigint <<= 1; 
  }
}

IPiece::IPiece()
  : Piece(bitboard::bigints::ipiece0, 
          bitboard::bigints::ipiece1, 
          bitboard::bigints::ipiece2,
          bitboard::bigints::ipiece3)
{
}

// rotation invariant
OPiece::OPiece()
  : Piece(bitboard::bigints::opiece)
{
}

void OPiece::rotateright()
{
}

void OPiece::rotateleft()
{
}

TPiece::TPiece()
  : Piece(bitboard::bigints::tpiece0, 
          bitboard::bigints::tpiece1, 
          bitboard::bigints::tpiece2,
          bitboard::bigints::tpiece3)
{
}

JPiece::JPiece()
  : Piece(bitboard::bigints::jpiece0, 
          bitboard::bigints::jpiece1, 
          bitboard::bigints::jpiece2,
          bitboard::bigints::jpiece3)
{
}

LPiece::LPiece()
  : Piece(bitboard::bigints::lpiece0, 
          bitboard::bigints::lpiece1, 
          bitboard::bigints::lpiece2,
          bitboard::bigints::lpiece3)
{
}

ZPiece::ZPiece()
  : Piece(bitboard::bigints::zpiece0, 
          bitboard::bigints::zpiece1, 
          bitboard::bigints::zpiece2,
          bitboard::bigints::zpiece3)
{
}

SPiece::SPiece()
  : Piece(bitboard::bigints::spiece0, 
          bitboard::bigints::spiece1, 
          bitboard::bigints::spiece2,
          bitboard::bigints::spiece3)
{
}

