#include "../include/agent.h"  // Agent
#include <string>              // string
#include <random>              // random_device mt19937 uniform_int_distribution

Agent::Agent(std::string name)
  : name{name} 
{
}

RandomAgent::RandomAgent()
  : Agent("random")
{
}

int RandomAgent::act(mp::uint256_t board)
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 4);
  return distrib(gen);
};
