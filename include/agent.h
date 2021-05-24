#ifndef AGENT_H
#define AGENT_H

#include "search.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <utility>                           // pair
#include <string>

// provide movement during game
// receive game board state, current piece, next piece

using boost::multiprecision::uint256_t;

class Agent
{
public:
  friend std::ostream& operator<<(std::ostream& os, const Agent& agent);

protected:  // abstract class
  Agent(std::string);

private:
  std::string name; 
};


class SearchPlayAgent : public PlayAgent
{
public:
  SearchPlayAgent();
  int act(uint256_t state,
          std::pair<uint256_t, int> cur_piece, 
          std::pair<uint256_t, int> nex_piece) override;

private:
  PlaySearch search;
  std::vector<int> actions;
};

/*
class LockAgent : public Agent
{
public:
  LockAgent();
  uint256_t act(uint256_t state,
                std::pair<uint256_t, int> cur_piece, 
                std::pair<uint256_t, int> nex_piece);

private:
  LockSearch search;
};
*/

#endif  // AGENT_H
