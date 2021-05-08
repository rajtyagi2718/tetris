#include "../include/graph.h"
#include "../include/bitboard.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <string>
#include <fstream>  // ifstream
#include <sstream>  // istringstream  
#include <iostream>

using boost::multiprecision::uint256_t;

Graph::Graph()
  : spawn_states{bitboard::tpiece0, bitboard::jpiece0, bitboard::zpiece0,
                 bitboard::opiece0, bitboard::spiece0, bitboard::lpiece0,
                 bitboard::ipiece0},
    gen{rd()}, distrib(0, 6)
{
  std::string file_name {"../build/afterstates_"};
  for (int id = 0; id < PieceId_END; id++)
  {
    std::ifstream file {file_name + std::to_string(id)};
    if (file.is_open())
    {
      std::string line;
      while (std::getline(file, line))
      {
        std::istringstream iss {line};
        uint256_t state;
        assert(iss >> state);
        afterstates[id][state];  // set array to zeros
        for (int action = 0; action < Action_END; ++action)
        {
          uint256_t afterstate;
          iss >> afterstate;
          afterstates[id][state][action] = afterstate; 
        }
      }
      file.close();
    }
    else
    {
      assert(false && "failed to open afterstates file");
    }
  }
  for (int id = 0; id < PieceId_END; id++)
  {
    assert(afterstates[id].size() > 100);
  }
}

std::pair<uint256_t, int> Graph::spawn()
{
  int id = distrib(gen);
  return {spawn_states[id], id};
}

void Graph::move(std::pair<uint256_t, int>& piece, int action)
{
  auto& [state, id] = piece;
  assert(afterstates[id].count(state));
  state = afterstates[id][state][action];
}
