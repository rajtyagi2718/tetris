#include "../include/graph.h"
#include "../include/bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <string>
#include <fstream>  // ifstream
#include <sstream>  // istringstream  

using boost::multiprecision::uint256_t;

Graph::Graph()
  : spawn_states{bitboard::tpiece0, bitboard::jpiece0, bitboard::zpiece0,
                 bitboard::opiece0, bitboard::spiece0, bitboard::lpiece0,
                 bitboard::ipiece0},
    gen{rd()}, distrib(0, 6)
{
  std::string file_name {"../build/after_states_"};
  for (int id = 0; id < PieceId_END; id++)
  {
    std::ifstream file {file_name + std::to_string(id) + ".txt"};
    if (file.is_open())
    {
      std::string line;
      while (std::getline(file, line))
      {
        std::istringstream iss {line};
        uint256_t state;
        assert(iss >> state);
        after_states[id][state];  // set array to zeros
        for (int action = 0; action < Action_END; ++action)
        {
          uint256_t after_state;
          iss >> after_state;
          after_states[id][state][action] = after_state; 
        }
      }
      file.close();
    }
    else
    {
      assert(false && "failed to open after_states file");
    }
  }
  for (int id = 0; id < PieceId_END; id++)
  {
    assert(after_states[id].size() > 100);
  }
}

std::pair<uint256_t, int> Graph::spawn()
{
  return {spawn_states[0], 0};
  int id = distrib(gen);
  return {spawn_states[id], id};
}

void Graph::move(std::pair<uint256_t, int>& piece, int action)
{
  auto& [state, id] = piece;
  assert(bitboard::countbits(state) == 4);
  assert(after_states[id].count(state));
  assert(after_states[id][state][action]);
  state = after_states[id][state][action];
}

void Graph::undo(std::pair<uint256_t, int>& piece, int action)
{
  move(piece, Action_END - action - 1); 
}

uint256_t Graph::get_after_state(uint256_t state, int id, int action)
{
  assert(bitboard::countbits(state) == 4);
  assert(after_states[id].count(state));
  assert(after_states[id][state][action]);
  return after_states[id][state][action];
}

uint256_t Graph::get_before_state(uint256_t state, int id, int action)
{
  return get_after_state(state, id, Action_END - action - 1); 
}
