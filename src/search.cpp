#include "../include/board.h"
#include "../include/graph.h"
#include "../include/search.h"
#include "../include/features.h"    // values
#include "../include/ids.h"         // Action
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <queue>
#include <utility>                  // pair
#include <algorithm>                // copy max_element
#include <iterator>                 // back_inserter
#include <cassert>                  // assert
#include <fstream>                  // ifstream
#include <iostream>
#include <sstream>
#include <string>

using boost::multiprecision::uint256_t; 

Search::Search()
  : board{}, graph{}, weights{},
    cur_after_states{}, cur_terminal_states{},
    cur_line_clears{}, cur_board_states{},
    nex_after_states{}, nex_terminal_states{}, nex_board_states{},
    best_value{}, best_cur_index{}, best_nex_index{}
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
  select();
  set_actions(actions);
  // std::cout << "search value: " << best_value << std::endl;
}

void Search::reset(uint256_t board_state,
                   std::pair<uint256_t, int> cur_piece,
                   std::pair<uint256_t, int> nex_piece)
{
  this->board_state = board_state;
  this->cur_piece = cur_piece;
  this->nex_piece = nex_piece;

  cur_after_states.clear();
  cur_terminal_states.clear();
  cur_line_clears.clear();
  cur_board_states.clear();
  nex_after_states.clear();
  nex_terminal_states.clear();
  nex_board_states.clear();

  best_value = -1e6;
  best_cur_index = -1;
  best_nex_index = -1;
}

void Search::explore()
{
  board.reset(board_state);
  board.remove(cur_piece.first);
  bfs(cur_piece, cur_after_states, cur_terminal_states, cur_board_states);

  for (auto cur_board_state : cur_board_states)
  {
    board.reset(cur_board_state);
    cur_line_clears.push_back(board.clear_lines());

    nex_after_states.push_back({});
    nex_terminal_states.push_back({});
    nex_board_states.push_back({});
    bfs(nex_piece, nex_after_states.back(), nex_terminal_states.back(),
        nex_board_states.back()); 
  }
}

void Search::bfs(std::pair<uint256_t, int>& piece,
                 std::map<uint256_t, int>& after_states,
                 std::vector<uint256_t>& terminal_states,
                 std::vector<uint256_t>& board_states)
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
      board_states.push_back(board.get_after_state(state));
    }
  }
}

void Search::select()
{
  for (int i = 0; i < cur_board_states.size(); ++i) 
  {
    for (int j = 0; j < nex_board_states[i].size(); ++j)
    {
      double value = evaluate(nex_board_states[i][j], cur_line_clears[i]);
      if (value > best_value)
      {
        best_value = value;
        best_cur_index = i;
        best_nex_index = j;
      }
    } 
  }

  // assert(best_value != -1e6);
  // assert(best_cur_index != -1);
  // assert(best_nex_index != -1);
}

void Search::set_actions(std::vector<int>& actions)
{
  int i = best_cur_index;
  int j = best_nex_index;
  backtrack(actions, cur_piece, cur_terminal_states[i], cur_after_states); 
}

void Search::backtrack(std::vector<int>& actions,
                       std::pair<uint256_t,int>& piece,
                       uint256_t state, std::map<uint256_t, int>& after_states)
{
  board.reset(board_state);
  board.remove(cur_piece.first);

  auto& [start_state, id] = piece;
  int action = down;
  actions.push_back(action);
  while (state != start_state)
  {
    action = after_states[state];
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
