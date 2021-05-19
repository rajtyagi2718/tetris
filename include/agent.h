#ifndef AGENT_H
#define AGENT_H

#include "search.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <utility>                           // pair
#include <string>

// provide action during game play
// receive game board state, current piece, next piece

using boost::multiprecision::uint256_t;

class Agent
{
public:
  Agent(std::string);
  friend std::ostream& operator<<(std::ostream& os, const Agent& agent);
  virtual int act(uint256_t state,
                  std::pair<uint256_t, int> cur_piece, 
                  std::pair<uint256_t, int> nex_piece) = 0;

private:
  std::string name; 
};

class RandomAgent : public Agent
{
  public:
    RandomAgent();
    int act(uint256_t state,
            std::pair<uint256_t, int> cur_piece, 
            std::pair<uint256_t, int> nex_piece) override;
};

class SearchAgent : public Agent
{
  public:
    SearchAgent();
    int act(uint256_t state,
            std::pair<uint256_t, int> cur_piece, 
            std::pair<uint256_t, int> nex_piece) override;

  private:
    Search search;
    std::vector<int> actions;
};

#endif  // AGENT_H
