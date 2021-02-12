#include "../include/piece.h"                // []Piece
#include "../include/bitboard.h"             // print width []piece[]
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <iostream>

namespace piece
{
Piece::Piece(uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3)  
  : rot{0}, rotations{r0, r1, r2, r3}
{
}

Piece::Piece(uint256_t r)  
  : rot{0}, rotations{r}
{
}

uint256_t Piece::getbigint()
{
  std::cout << "piece getter" << std::endl;
  return rotations[rot];
}

const uint256_t& Piece::getbigint() const
{
  std::cout << "piece const getter" << std::endl;
  return rotations[rot];
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
  return bitboard::print(os, piece.getbigint(), false);
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
    bigint >>= bitboard::width; 
  }
}

void Piece::down()
{
  for (auto& bigint : rotations)
  {
    bigint <<= bitboard::width; 
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
  : Piece(bitboard::ipiece0, 
          bitboard::ipiece1, 
          bitboard::ipiece2,
          bitboard::ipiece3)
{
}

// rotation invariant
OPiece::OPiece()
  : Piece(bitboard::opiece)
{
}

void OPiece::rotateright()
{
}

void OPiece::rotateleft()
{
}

TPiece::TPiece()
  : Piece(bitboard::tpiece0, 
          bitboard::tpiece1, 
          bitboard::tpiece2,
          bitboard::tpiece3)
{
}

JPiece::JPiece()
  : Piece(bitboard::jpiece0, 
          bitboard::jpiece1, 
          bitboard::jpiece2,
          bitboard::jpiece3)
{
}

LPiece::LPiece()
  : Piece(bitboard::lpiece0, 
          bitboard::lpiece1, 
          bitboard::lpiece2,
          bitboard::lpiece3)
{
}

ZPiece::ZPiece()
  : Piece(bitboard::zpiece0, 
          bitboard::zpiece1, 
          bitboard::zpiece2,
          bitboard::zpiece3)
{
}

SPiece::SPiece()
  : Piece(bitboard::spiece0, 
          bitboard::spiece1, 
          bitboard::spiece2,
          bitboard::spiece3)
{
}
}  // namespace piece 
