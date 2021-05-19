#ifndef BOARD_H
#define BOARD_H

#include "bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>

// bitboard interface for grapher, game, search
// modify state given changes to piece  
// clear filled lines as pieces fall to bottom

using boost::multiprecision::uint256_t;

class Board
{
public:
  Board();
  Board(uint256_t state);
  const uint256_t& get_state() const;
  void reset(uint256_t state = bitboard::board);
  friend std::ostream& operator<<(std::ostream& os, const Board& board);
  bool is_valid(const uint256_t& piece);  
  void add(const uint256_t& piece);  
  bool try_add(const uint256_t& piece);  
  void remove(const uint256_t& piece);  
  uint256_t get_after_state(const uint256_t& piece);  // add piece, return state
  int clear_lines();

private:
  uint256_t state;
};

#endif  // BOARD_H
