#include "../include/piece.h"                // []Piece
#include "../include/bitboard.h"             // print width []piece[]
#include "../include/exception.h"            // SpawnPieceIndexException
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <iostream>
#include <memory>                            // unique_ptr make_unique
#include <random>                            // random_device mt19937 uniform_int_distribution

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

bool Piece::top() const
{
  uint256_t upper {bitboard::line}; 
  upper = upper | (upper << bitboard::width);
  return !(getbigint() & ~upper);
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

std::unique_ptr<Piece> spawnpiece()
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 6);
  int p = distrib(gen);
  switch (p)
  {
    case 0: return std::make_unique<IPiece>();
    case 1: return std::make_unique<OPiece>();
    case 2: return std::make_unique<TPiece>();
    case 3: return std::make_unique<JPiece>();
    case 4: return std::make_unique<LPiece>();
    case 5: return std::make_unique<ZPiece>();
    case 6: return std::make_unique<SPiece>();
  }
  
  SpawnPieceIndexException exc {p};
  throw exc;
}
