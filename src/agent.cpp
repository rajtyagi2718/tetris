#include "../include/agent.h"
#include "../include/bitboard.h"             // print
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <string>
#include <random>  // random_device mt19937 uniform_int_distribution
#include <iostream>

using boost::multiprecision::uint256_t;

Agent::Agent(std::string name)
  : name{name} 
{
}

std::ostream& operator<<(std::ostream& os, const Agent& agent)
{
  os << agent.name;
  return os;
}

/*
LockAgent::LockAgent()
  : Agent("search"), search{}
{
}

uint256_t LockAgent::act(uint256_t state,
                         std::pair<uint256_t, int> cur_piece, 
                         std::pair<uint256_t, int> nex_piece)
{
  return search.run(state, cur_piece, nex_piece);
}
*/
