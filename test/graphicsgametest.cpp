#include "../include/graphicsgame.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <gtest/gtest.h> 
#include <sstream>
#include <iostream>

namespace graphicsgametest
{
TEST(GraphicsGameTest, Constructor)
{
  RandomAgent randomagent{};
  Board board{};
  std::ostringstream msg{};
  // GraphicsGame<RandomAgent> graphicsgame{randomagent, board, msg};
  GraphicsGame<RandomAgent> graphicsgame{randomagent, board, std::cout};
  graphicsgame.play();
}
}  // namespace graphicsgametest
