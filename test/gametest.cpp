// TODO  GameTest Combine Random, Search
#include "../include/game.h"                 //
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <gtest/gtest.h>                     // 
#include <iostream>                          // cout endl
#include <sstream>                           // ostringstream

namespace gametest
{
using ::testing::TestWithParam;
using ::testing::Range;

class Random : public TestWithParam<int>
{
protected:
  Random() 
    : randomagent{}, board{}, msg{}, game{randomagent, board, msg}
  {}
  RandomAgent randomagent;
  Board board;
  std::ostringstream msg;
  Game<RandomAgent> game; 
};

TEST_P(Random, Play)
{
  game.play();
  // std::cout << msg.str() << std::endl;
}

INSTANTIATE_TEST_CASE_P(GameTest, Random, Range(0, 0));

class Search : public TestWithParam<int>
{
protected:
  Search()
   : searchagent{}, board{}, msg{}, game{searchagent, board, std::cout}
  {}
  SearchAgent searchagent;
  Board board;
  std::ostringstream msg;
  Game<SearchAgent> game; 
};

TEST_P(Search, Play)
{
  std::cout << "HERE" << std::endl;
  game.play();
  // std::cout << msg.str() << std::endl;
}

INSTANTIATE_TEST_CASE_P(GameTest, Search, Range(0, 10));
}  // namespace gametest
