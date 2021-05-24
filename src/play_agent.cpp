#include "play_agent.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <utility>                           // pair
#include <string>

PlayAgent::PlayAgent(std::string name)
  : Agent(name)
{
}

RandomPlayAgent::RandomPlayAgent()
  : PlayAgent("random_play")
{
}

int RandomPlayAgent::act(uint256_t state,
                     std::pair<uint256_t, int> cur_piece, 
                     std::pair<uint256_t, int> nex_piece)
{
  static std::random_device rd; 
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<> distrib(0, 4);
  return distrib(gen);
}

SearchPlayAgent::SearchPlayAgent()
  : PlayAgent("search_play"), search{}, actions{}
{
  actions.reserve(20);
}

int SearchPlayAgent::act(uint256_t state,
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
