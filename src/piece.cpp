#include "../include/piece.h"
#include "../include/bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <memory>                            // unique_ptr make_unique
#include <cassert>                           // assert

#include <iostream>

Piece::Piece(uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3)  
  : rot{0}, num_rot{4}, rotations{r0, r1, r2, r3}
{
}

Piece::Piece(uint256_t r0, uint256_t r1)  
  : rot{0}, num_rot{2}, rotations{r0, r1}
{
}

Piece::Piece(uint256_t r0)  
  : rot{0}, num_rot{1}, rotations{r0}
{
}

uint256_t Piece::get_state()
{
  return rotations[rot];
}

const uint256_t& Piece::get_state() const
{
  return rotations[rot];
}


std::vector<uint256_t> Piece::get_rotations()
{
  return rotations;
}

void Piece::down()
{
  for (auto& state : rotations)
  {
    state <<= bitboard::width; 
  }
}

void Piece::rotate_left()
{
  rot = (rot - 1) % num_rot;
} 

void Piece::left()
{
  for (auto& state : rotations)
  {
    state >>= 1; 
  }
}

void Piece::right()
{
  for (auto& state : rotations)
  {
    state <<= 1; 
  }
}

void Piece::rotate_right()
{
  rot = (rot + 1) % num_rot; 
} 

void Piece::up()
{
  for (auto& state : rotations)
  {
    state >>= bitboard::width; 
  }
}

bool Piece::is_top() const
{
  return !!(get_state() & bitboard::top);
  /*
  uint256_t upper {bitboard::line}; 
  upper = upper | (upper << bitboard::width);
  return !(get_state() & ~upper);
  */
}

bool Piece::is_bottom() const
{
  return !!(get_state() & bitboard::bottom);
}

bool Piece::is_floor() const
{
  return !!(get_state() & bitboard::floor);
}

bool Piece::is_valid() const
{
  for (auto x : rotations)
  {
    if (bitboard::countbits(x) != 4)
    {
      return false;
    }
  }
  return true;
}

TPiece::TPiece()
  : Piece(bitboard::tpiece0, bitboard::tpiece1, 
          bitboard::tpiece2, bitboard::tpiece3)
{
}

JPiece::JPiece()
  : Piece(bitboard::jpiece0, bitboard::jpiece1, 
          bitboard::jpiece2, bitboard::jpiece3)
{
}

ZPiece::ZPiece()
  : Piece(bitboard::zpiece0, bitboard::zpiece1)
{
}

OPiece::OPiece()
  : Piece(bitboard::opiece0)
{
}

SPiece::SPiece()
  : Piece(bitboard::spiece0, bitboard::spiece1)
{
}

LPiece::LPiece()
  : Piece(bitboard::lpiece0, bitboard::lpiece1, 
          bitboard::lpiece2, bitboard::lpiece3)
{
}

IPiece::IPiece()
  : Piece(bitboard::ipiece0, bitboard::ipiece1)
{
}

std::unique_ptr<Piece> spawn_piece(int id)
{
  switch (id)
  {
    case tpiece: return std::make_unique<TPiece>();
    case jpiece: return std::make_unique<JPiece>();
    case zpiece: return std::make_unique<ZPiece>();
    case opiece: return std::make_unique<OPiece>();
    case spiece: return std::make_unique<SPiece>();
    case lpiece: return std::make_unique<LPiece>();
    case ipiece: return std::make_unique<IPiece>();
    default: assert(false && "spawn piece id out of range [0, 6].");
  }
}

uint256_t down_state(uint256_t& state)
{ 
  return state << bitboard::width;
}

uint256_t left_state(uint256_t& state)
{ 
  return state >> 1;
}

uint256_t right_state(uint256_t& state)
{ 
  return state << 1;
}
