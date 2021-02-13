#include "../include/game.h"                 // Game
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <gtest/gtest.h>                     // TEST EXPECT_TRUE
#include <iostream>                          // cout endl

namespace gametest
{
TEST(GameTest, Constructor)
{
  RandomAgent randomagent {};
  Board board {};
  Game<RandomAgent> game {randomagent, board, std::cout}; 
}

TEST(GameTest, Play)
{
  RandomAgent randomagent {};
  Board board {};
  Game<RandomAgent> game {randomagent, board, std::cout}; 
  game.play();
}
}  // namespace gametest
