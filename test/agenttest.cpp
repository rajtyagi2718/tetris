#include "../include/agent.h"     // RandomAgent
#include "../include/bitboard.h"  // board
#include <gtest/gtest.h>          // TEST EXPECT_TRUE

namespace agenttest
{
TEST(RandomAgentTest, Act)
{
  RandomAgent ra{};
  for (int i = 0; i < 10; i++)
  {
    ra.act(0, 0, 0);
  }
}

TEST(SearchAgentTest, Act)
{
  SearchAgent sa{};
  for (int i = 0; i < 10; i++)
  {
    sa.act(bitboard::board, 0, 0);
  }
}
}  // namespace agenttest
