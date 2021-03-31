// TODO Combine Random, Search Agent tests
#include "../include/graphicsgame.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/piece.h"
#include <gtest/gtest.h> 
#include <sstream>
#include <iostream>

namespace graphicsgametest
{
// TEST(GraphicsGameRandomAgentTest, Constructor)
// {
//   RandomAgent randomagent{};
//   Board board{};
//   std::ostringstream msg{};
//   GraphicsGame<RandomAgent> graphicsgame{randomagent, board, msg};
//   graphicsgame.play();
// }

TEST(GraphicsGameSearchAgentTest, Constructor)
{
  SearchAgent searchagent{};
  Board board{};
  GraphicsGame<SearchAgent> graphicsgame{searchagent, board, std::cout};
  graphicsgame.play();
}
}  // namespace graphicsgametest
