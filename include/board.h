#ifndef BOARD_H
#define BOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream

using boost::multiprecision::uint256_t;

class Board
{
public:
  Board();
  Board(uint256_t state);
  uint256_t get_state();
  const uint256_t& get_state() const;
  void reset();
  friend std::ostream& operator<<(std::ostream& os, const Board& board);
  bool is_valid(const uint256_t& piece);  
  void add(const uint256_t& piece);  
  bool try_add(const uint256_t& piece);  
  void remove(const uint256_t& piece);  
  int clear_lines();

private:
  uint256_t state;
};

#endif  // BOARD_H
