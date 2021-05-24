#ifndef LOCK_AGENT_H
#define LOCK_AGENT_H

#include "agent.h"
#include "lock_search.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <utility>                           // pair
#include <string>

// provide movement during game
// receive game board state, current piece, next piece

using boost::multiprecision::uint256_t;

class LockAgent : public Agent
{
public:
  LockAgent();
  virtual uint256_t act(uint256_t state,
                        std::pair<uint256_t, int> cur_piece, 
                        std::pair<uint256_t, int> nex_piece) = 0;
};

class SearchLockAgent : public LockAgent
{
public:
  SearchLockAgent();
  int act(uint256_t state,
          std::pair<uint256_t, int> cur_piece, 
          std::pair<uint256_t, int> nex_piece) override;

private:
  LockSearch search;
};

#endif  // LOCK_AGENT_H
