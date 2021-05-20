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
    std::cout << "actions: ";
  } 
  int ret = actions.back();
  actions.pop_back();
  std::cout << ret << ' ';
  return ret;
}
