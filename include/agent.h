#ifndef AGENT_H
#define AGENT_H

#include "search.h"
#include <boost/multiprecision/cpp_int.hpp>    // uint256_t
#include <vector>                              // vector #include <utility>                             // pair
#include <string>                              // string
#include <sstream>                             // ostream

using boost::multiprecision::uint256_t;

// enum Action {null, rotateleft, left, right, rotateright, Action_END};

class Agent
{
public:
  Agent(std::string);
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
