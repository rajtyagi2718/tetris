#ifndef GRAPHER_H
#define GRAPHER_H

#include "bitboard.h"
#include "piece.h"
#include "board.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <map>
#include <set>
#include <array>

using boost::multiprecision::uint256_t;

class Grapher
{
enum Action {down, rotate_left, left, right, rotate_right, up, Action_END};

public:
  Grapher();
  void dfs(); 
  
private: 
  Board board; 
  std::unique_ptr<Piece> piece; 
  std::vector<uint256_t> states;
  std::map<uint256_t, std::array<uint256_t, Action_END>> after_states;
  std::set<uint256_t> tops;

  void enumerate_tops();
  void explore(uint256_t state);
  void explore_floor(uint256_t state);
  void forward(int action);
  void backward(int action);

  void write_after_states(int id);
};

#endif  // GRAPHER_H
