#include "../include/bitboard.h"  // print
#include "../include/agent.h"  // Agent
#include <boost/multiprecision/cpp_int.hpp>    // uint256_t
#include <string>              // string
#include <random>              // random_device mt19937 uniform_int_distribution
#include <iostream>

using boost::multiprecision::uint256_t;

Agent::Agent(std::string name)
  : name{name} 
{
}

RandomAgent::RandomAgent()
  : Agent("random")
{
}

int RandomAgent::act(uint256_t state,
                     std::pair<uint256_t, int> piece, 
                     std::pair<uint256_t, int> next_piece)
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 4);
  return distrib(gen);
}

SearchAgent::SearchAgent()
  : Agent("search"), actions{}
{
  actions.reserve(20);
}

int SearchAgent::act(uint256_t state,
                     std::pair<uint256_t, int> piece, 
                     std::pair<uint256_t, int> next_piece)
{
  return 0;
  if (actions.empty())
  {
    // searchgame.search(state, piece, next_piece);
    assert(!actions.empty());
  } 
  auto [piece_state, ret] = actions.back();
  assert(piece.first == piece_state);
  actions.pop_back();
  return ret;
}
