#include "../include/search.h"
#include "../include/board.h"
#include "../include/graph.h"
#include "../include/features.h"  // values
#include "../include/ids.h"       // Action
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <queue>
#include <utility>                // pair
#include <algorithm>              // max
#include <cassert>                // assert
#include <fstream>                // ifstream
#include <iostream>
#include <sstream>
#include <string>

using boost::multiprecision::uint256_t; 

Search::Search()
  : board{}, graph{}, weights{},
    cur_after_states{}, cur_terminal_states{},
    nex_after_states{}, nex_terminal_states{},
    pre_after_states{}, pre_terminal_states{},
    best_value{}, best_terminal_state{}
{
  std::ifstream file {"../src/weights.txt"};
  if (file.is_open())
  {
    std::string line;
    std::getline(file, line);
    std::istringstream iss {line};
    double weight;
    while (iss >> weight)
    {
      weights.push_back(weight);
    }
    file.close();
  } 
  else
  {
    assert(false && "cannot open weights.txt file");
  }
}

void Search::run(uint256_t board_state,
                 std::pair<uint256_t, int> cur_piece,
                 std::pair<uint256_t, int> nex_piece,
                 std::vector<int>& actions)
{
  reset(board_state, cur_piece, nex_piece);
  explore();
  std::cout << "search value: " << best_value << std::endl;
  backtrack(actions); 
}

void Search::reset(uint256_t board_state,
                   std::pair<uint256_t, int> cur_piece,
                   std::pair<uint256_t, int> nex_piece)
{
  board.reset(board_state); 
  board.remove(cur_piece.first);
  this->board_state = board.get_state();

  this->cur_piece = cur_piece;
  if (cur_after_states.empty())
  {
    cur_after_states.clear();
    cur_terminal_states.clear();
    bfs(cur_piece, cur_after_states, cur_terminal_states);
  }
  else
  {
    cur_after_states = std::move(pre_after_states);
    cur_terminal_states = std::move(pre_terminal_states);
  }

  this->nex_piece = nex_piece;
  nex_after_states.clear();
  nex_terminal_states.clear();

  best_value = -1e6;
  best_terminal_state = 0;
}

void Search::explore()
{
  for (auto cur_terminal_state : cur_terminal_states)
  {
    board.reset(board_state);
    board.add(cur_terminal_state);
    int lines = board.clear_lines();
    nex_after_states.clear();
    nex_terminal_states.clear();
    bfs(nex_piece, nex_after_states, nex_terminal_states);
    update_best(cur_terminal_state, lines); 
  }
}

void Search::bfs(std::pair<uint256_t, int>& piece,
                 std::map<uint256_t, int>& after_states,
                 std::vector<uint256_t>& terminal_states)
{
  auto [state, id] = piece;
  std::queue<uint256_t> states;
  states.push(state);

  while (!states.empty())
  {
    uint256_t state = states.front();
    states.pop();
    // assert(board.is_valid(state));
    uint256_t after_state;
    for (int action = 1; action < Action_END-1; ++action)
    {
      after_state = graph.get_after_state(state, id, action);
      if (board.is_valid(after_state) && !after_states.count(after_state))
      {
        after_states[after_state] = action;
        states.push(after_state);
      }
    }
    after_state = graph.get_after_state(state, id, 0);
    if (board.is_valid(after_state))
    {
      after_states[after_state] = 0;
      states.push(after_state);
    }
    else
    {
      terminal_states.push_back(state);
    }
  }
}

void Search::update_best(uint256_t& cur_terminal_state, int lines)
{
  double value = -1e6;
  for (auto& nex_terminal_state : nex_terminal_states)
  {
    value = std::max(value, 
      evaluate(board.get_after_state(nex_terminal_state), lines));
  }
  if (value > best_value)
  {
    best_value = value;
    best_terminal_state = cur_terminal_state; 
    pre_after_states = std::move(nex_after_states);
    pre_terminal_states = std::move(nex_terminal_states);
  }
}

void Search::backtrack(std::vector<int>& actions)
{
  uint256_t state = best_terminal_state;
  auto& [start_state, id] = cur_piece;
  int action = down;
  actions.push_back(action);
  while (state != start_state)
  {
    action = cur_after_states[state];
    state = graph.get_before_state(state, id, action);
    actions.push_back(action);
  } 
}

double Search::evaluate(uint256_t board_state, int cur_line_clear)
{
  std::vector<double> values = features::values(board_state, cur_line_clear);
  auto it = weights.cbegin();
  auto jt = values.cbegin();
  double ret = 0.0;
  while (it != weights.cend())
  {
    ret += *it * *jt;
    it++;
    jt++; 
  }
  return ret;
}
