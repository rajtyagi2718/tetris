#include "agent.h"
#include "lock_search.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <utility>                           // pair
#include <string>

LockAgent::LockAgent(std::string name)
  : Agent(name)
{
}

SearchLockAgent::SearchLockAgent()
  : LockAgent("search_lock"), search{}
{
}

int SearchLockAgent::act(uint256_t state,
                     std::pair<uint256_t, int> cur_piece, 
                     std::pair<uint256_t, int> nex_piece)
{
  return search.run(state, cur_piece, nex_piece);
}
