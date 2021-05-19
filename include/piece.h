#ifndef PIECE_H
#define PIECE_H

#include "ids.h"   // PieceId
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <memory>                            // unique_ptr

// dynamically create, move pieces for grapher
// reduced to (state, id) pair in game, graph

namespace make_graph
{
using boost::multiprecision::uint256_t;

class Piece
{
public:
  uint256_t get_state();
  const uint256_t& get_state() const;
  std::vector<uint256_t> get_rotations();

  void down();
  void rotate_left();
  void left();
  void right();
  void rotate_right();
  void up();

  bool is_top() const;
  bool is_bottom() const;
  bool is_floor() const;
  bool is_valid() const;

protected:  
  // abstract class
  Piece(uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3);  
  Piece(uint256_t r0, uint256_t r1);  
  Piece(uint256_t r);  

private:
  unsigned int rot;
  unsigned int num_rot;
  std::vector<uint256_t> rotations;
};

class TPiece : public Piece
{
public:
  TPiece();
};

class JPiece : public Piece
{
public:
  JPiece();
};

class ZPiece : public Piece
{
public:
  ZPiece();
};

class OPiece : public Piece
{
public:
  OPiece();
};

class SPiece : public Piece
{
public:
  SPiece();
};

class LPiece : public Piece
{
public:
  LPiece();
};

class IPiece : public Piece
{
public:
  IPiece();
};

std::unique_ptr<Piece> spawn_piece(int id);

uint256_t down_state(uint256_t& state);
uint256_t left_state(uint256_t& state);
uint256_t right_state(uint256_t& state);
}  // namespace make_graph

#endif  // PIECE_H
