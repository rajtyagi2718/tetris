#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"
#include "graph.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>  // pair
#include <memory>   // unique_ptr

using boost::multiprecision::uint256_t; 

class Search
{
public:
  Search();
  void run(uint256_t board_state,
           std::pair<uint256_t, int> cur_piece,
           std::pair<uint256_t, int> nex_piece,
           std::vector<int>& actions);

private:
  Board board; 
  Graph graph;
  std::vector<double> weights;
  
  uint256_t board_state;
  std::pair<uint256_t, int> cur_piece;
  std::pair<uint256_t, int> nex_piece;

  std::map<uint256_t, int> cur_after_states;
  std::vector<uint256_t> cur_terminal_states;
  std::map<uint256_t, int> nex_after_states;
  std::vector<uint256_t> nex_terminal_states;
  std::map<uint256_t, int> pre_after_states;
  std::vector<uint256_t> pre_terminal_states;

  double best_value;
  uint256_t best_terminal_state;

  void reset(uint256_t board_state,
             std::pair<uint256_t, int> cur_piece,
             std::pair<uint256_t, int> nex_piece);
  void explore();
  void bfs(std::pair<uint256_t, int>& piece,
           std::map<uint256_t, int>& after_states,
           std::vector<uint256_t>& terminal_states);
  void update_best(uint256_t& cur_terminal_state, int lines);
  double evaluate(uint256_t board_state, int cur_line_clear);
  void backtrack(std::vector<int>& actions);
};

#endif  // SEARCH_H
