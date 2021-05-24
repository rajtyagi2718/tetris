#ifndef PLAY_AGENT_H
#define PLAY_AGENT_H

#include "agent.h"
#include "play_search.h"
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>
#include <utility>                           // pair
#include <string>

// return action during game play

using boost::multiprecision::uint256_t;

class PlayAgent : public Agent
{
public:
  PlayAgent(std::string);
  virtual int act(uint256_t state,
                  std::pair<uint256_t, int> cur_piece, 
                  std::pair<uint256_t, int> nex_piece) = 0;
};

class RandomPlayAgent : public PlayAgent
{
public:
  RandomPlayAgent();
  int act(uint256_t state,
          std::pair<uint256_t, int> cur_piece, 
          std::pair<uint256_t, int> nex_piece) override;
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
