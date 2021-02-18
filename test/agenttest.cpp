#include "../include/agent.h"  // RandomAgent
#include <gtest/gtest.h>       // TEST EXPECT_TRUE

namespace agenttest
{
TEST(AgentTest, Act)
{
  RandomAgent ra{};
  for (int i = 0; i < 10; i++)
  {
    ra.act(0);
  }
}
}  // namespace agenttest
