#include "../include/agent.h"  // Agent
#include <boost/multiprecision/cpp_int.hpp>    // uint256_t
#include <string>              // string
#include <random>              // random_device mt19937 uniform_int_distribution

using boost::multiprecision::uint256_t;

Agent::Agent(std::string name)
  : name{name} 
{
}

RandomAgent::RandomAgent()
  : Agent("random")
{
}

int RandomAgent::act(uint256_t boardint, uint256_t pieceint, int pieceid)
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 4);
  return distrib(gen);
}

SearchAgent::SearchAgent()
  : Agent("search"), searchgame{}, actions{}
{
  actions.reserve(20);
}

int SearchAgent::act(uint256_t boardint, uint256_t pieceint, int pieceid)
{
  if (actions.empty())
  {
    searchgame.reset(boardint, pieceid);
    searchgame.search();
    searchgame.bestactions(actions);
  } 
  int ret = actions.back();
  actions.pop_back();
  return ret;
}
