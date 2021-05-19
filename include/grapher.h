#ifndef GRAPHER_H
#define GRAPHER_H

#include "board.h"
#include "piece.h"
#include "ids.h"    // Action
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <map>
#include <set>
#include <array>

// generate all piece (state, action, after_state) triplets
// write graph to file

namespace make_graph
{
using boost::multiprecision::uint256_t;

class Grapher
{

public:
  Grapher();
  void make();
  
private: 
  Board board; 
  std::unique_ptr<Piece> piece; 
  std::vector<uint256_t> states;
  std::map<uint256_t, std::array<uint256_t, Action_END>> after_states;
  std::set<uint256_t> tops;  // all states reacheable left right rotate

  void fill_tops();
  void dfs(uint256_t state);  // depth first search
  void search_floor(uint256_t state);
  void forward(int action);
  void backward(int action);

  void write_after_states(int id);
};
}  // namespace make_graph

#endif  // GRAPHER_H
