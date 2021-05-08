#include "../include/bitboard.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <unordered_map>
#include <vector>

using boost::multiprecision::uint256_t;

class Graph
{
public:
  Graph();
  uint256_t spawn_piece() const;
  uint256_t move_piece(const uint256_t& piece, int action) const;
  print_piece(std::ostream& os, const uint256_t& piece) const;

private:
  unordered_map<uint256_t, std::vector<uint256_t>> adj;
  void load_adj();
};
