#include "../include/piece.h"                // []Piece
#include "../include/bitboard.h"             // print width []piece[]
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream
#include <iostream>
#include <memory>                            // unique_ptr make_unique
#include <random>                            // random_device mt19937 uniform_int_distribution
#include <cassert>                           // assert

Piece::Piece(int id, uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3)  
  : id{id}, rot{0}, numrot{4}, rotations{r0, r1, r2, r3}
{
}

Piece::Piece(int id, uint256_t r0, uint256_t r1)  
  : id{id}, rot{0}, numrot{2}, rotations{r0, r1}
{
}

Piece::Piece(int id, uint256_t r0)  
  : id{id}, rot{0}, numrot{1}, rotations{r0}
{
}

uint256_t Piece::getbigint()
{
  //std::cout << "piece getter" << std::endl;
  return rotations[rot];
}

const uint256_t& Piece::getbigint() const
{
  //std::cout << "piece const getter" << std::endl;
  return rotations[rot];
}

int Piece::getid() const
{
  return id;
}

unsigned int Piece::getrot() const
{
  return rot;
}

std::ostream& operator<<(std::ostream& os, const Piece& piece)
{
  return bitboard::print(os, piece.getbigint());
}

void Piece::rotateright()
{
  rot = (rot + 1) % numrot; 
} 

void Piece::rotateleft()
{
  rot = (rot - 1) % numrot;
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

bool Piece::valid() const
{
  for (auto& x : rotations)
  {
    if (bitboard::countbits(x) != 4)
    {
      return false;
    }
  }
  return true;
}

std::ostream& Piece::printrotations(std::ostream& os) const
{
  for (int i = 0; i < numrot; i++)
  {
    os << "rot " << i << std::endl; 
    bitboard::print(os, rotations[i]);
    os << std::endl;
  }
  return os;
}

TPiece::TPiece()
  : Piece(tpiece,
          bitboard::tpiece0, bitboard::tpiece1, 
          bitboard::tpiece2, bitboard::tpiece3)
{
}

JPiece::JPiece()
  : Piece(jpiece,
          bitboard::jpiece0, bitboard::jpiece1, 
          bitboard::jpiece2, bitboard::jpiece3)
{
}

ZPiece::ZPiece()
  : Piece(zpiece, bitboard::zpiece0, bitboard::zpiece1)
{
}

OPiece::OPiece()
  : Piece(opiece, bitboard::opiece0)
{
}

SPiece::SPiece()
  : Piece(spiece, bitboard::spiece0, bitboard::spiece1)
{
}

LPiece::LPiece()
  : Piece(lpiece,
          bitboard::lpiece0, bitboard::lpiece1, 
          bitboard::lpiece2, bitboard::lpiece3)
{
}

IPiece::IPiece()
  : Piece(ipiece, bitboard::ipiece0, bitboard::ipiece1)
{
}

std::unique_ptr<Piece> spawnpiece()
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 6);
  return spawnpieceid(distrib(gen));
}

std::unique_ptr<Piece> spawnpieceid(int id)
{
  switch (id)
  {
    case ipiece: return std::make_unique<IPiece>();
    case opiece: return std::make_unique<OPiece>();
    case tpiece: return std::make_unique<TPiece>();
    case jpiece: return std::make_unique<JPiece>();
    case lpiece: return std::make_unique<LPiece>();
    case zpiece: return std::make_unique<ZPiece>();
    case spiece: return std::make_unique<SPiece>();
    default: assert(false && "spawn piece id out of range [0, 6].");
  }
}
