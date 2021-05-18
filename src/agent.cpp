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
                     std::pair<uint256_t, int> cur_piece, 
                     std::pair<uint256_t, int> nex_piece)
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
                     std::pair<uint256_t, int> cur_piece, 
                     std::pair<uint256_t, int> nex_piece)
{
  if (actions.empty())
  {
    search.run(state, cur_piece, nex_piece, actions);
    assert(!actions.empty());
  } 
  auto [expected_state, action] = actions.back();
  /*
  if (expected_state != state)
  {
    std::cout << "expected_state" << std::endl;
    bitboard::print(std::cout, expected_state);
    std::cout << std::endl;
    assert(false);
  }
  */
  assert(expected_state == state);
  // int ret = actions.back();
  actions.pop_back();
  return action;
}
