#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"
#include "graph.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>   // vector
#include <unordered_map>  // unordered_map 
#include <set>      // set
#include <utility>  // pair
#include <memory>   // unique_ptr

using boost::multiprecision::uint256_t; 

// TODO Action enum duplicate Grapher, Graph, Agent classes
enum Action {down, rotate_left, left, right, rotate_right, up, Action_END};

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
  std::vector<int> cur_line_clears;
  std::vector<uint256_t> cur_board_states;
  std::vector<std::map<uint256_t, int>> nex_after_states;
  std::vector<std::vector<uint256_t>> nex_terminal_states;
  std::vector<std::vector<uint256_t>> nex_board_states;

  double best_value;
  int best_cur_index;
  int best_nex_index;

  void reset(uint256_t board_state,
             std::pair<uint256_t, int> cur_piece,
             std::pair<uint256_t, int> nex_piece);
  void explore();
  void bfs(std::pair<uint256_t, int>& piece,
           std::map<uint256_t, int>& after_states,
           std::vector<uint256_t>& terminal_states,
           std::vector<uint256_t>& board_states);
  void select();
  void set_actions(std::vector<int>& actions);
  void backtrack(std::vector<int>& actions, std::pair<uint256_t,int>& piece,
                 uint256_t state, std::map<uint256_t, int>& after_states);
  double evaluate(uint256_t board_state, int cur_line_clear);
};

#endif  // SEARCH_H
