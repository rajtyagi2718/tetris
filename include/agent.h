#ifndef AGENT_H
#define AGENT_H

#include <boost/multiprecision/cpp_int.hpp>    // uint256_t
#include <string>                              // string
#include <sstream>                             // ostream

using boost::multiprecision::uint256_t;

enum Action {null, rotateright, rotateleft, left, right};

class Agent
{
  public:
    Agent(std::string);
    virtual int act(uint256_t board) = 0;  // abstract class
  
  private:
    std::string name; 
};

class RandomAgent : public Agent
{
  public:
    RandomAgent();
    int act(uint256_t board) override;
};

#endif  // AGENT_H
