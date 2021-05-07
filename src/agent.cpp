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

int RandomAgent::act(uint256_t boardint, uint256_t pieceint, int pieceid, int nexpieceid)
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

int SearchAgent::act(uint256_t boardint, uint256_t pieceint, int pieceid, int nexpieceid)
{
  if (actions.empty())
  {
    // std::cout << "empty" << std::endl;
    searchgame.search(boardint, pieceid, nexpieceid, actions);
    assert(!actions.empty());
    /*
    std::cout << "actions size " << actions.size() << std::endl;
    for (auto it = actions.crbegin(); it != actions.crend(); it++)
    {
      std::cout << it->second << ' ';
    }
    std::cout << std::endl;
    */
  } 
  auto [state, ret] = actions.back();
  assert(state == boardint);
  // if (state != boardint)
  // {
  //   std::cout << "\nactual state\n" << boardint << std::endl;
  //   bitboard::print(std::cout, boardint);
  //   std::cout << "expected state\n" << state << std::endl;
  //   bitboard::print(std::cout, state);
  //   assert(state == boardint);
  // }
  // else
  // {
  //   std::cout << "states agree, size " << actions.size() << std::endl;
  // }
  actions.pop_back();
  return ret;
}
