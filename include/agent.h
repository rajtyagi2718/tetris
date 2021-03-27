#ifndef AGENT_H
#define AGENT_H

#include "../include/searchgame.h"
#include <boost/multiprecision/cpp_int.hpp>    // uint256_t
#include <vector>                              // vector
#include <string>                              // string
#include <sstream>                             // ostream

using boost::multiprecision::uint256_t;

enum Action {null, rotateleft, left, right, rotateright, Action_END};

class Agent
{
public:
  Agent(std::string);
  virtual int act(uint256_t boardint, uint256_t pieceint, int pieceid) = 0;

private:
  std::string name; 
};

class RandomAgent : public Agent
{
  public:
    RandomAgent();
    int act(uint256_t boardint, uint256_t pieceint, int pieceid) override;
};

class SearchAgent : public Agent
{
  public:
    SearchAgent();
    int act(uint256_t boardint, uint256_t pieceint, int pieceid) override;

  private:
    SearchGame searchgame;
    std::vector<int> actions;
};

#endif  // AGENT_H
