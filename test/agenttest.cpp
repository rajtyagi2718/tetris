#include "../include/agent.h"  // RandomAgent
#include <gtest/gtest.h>       // TEST EXPECT_TRUE

namespace agenttest
{
TEST(AgentTest, Throw)
{
  RandomAgent ra{};
  std::cout << "random agent actions\t";
  for (int i = 0; i < 10; i++)
  {
     std::cout << ra.act(0) << ' ';
  }
  std::cout << std::endl;

  RandomAgent rb{};
  std::cout << "random agent actions\t";
  for (int i = 0; i < 10; i++)
  {
     std::cout << rb.act(0) << ' ';
  }
  std::cout << std::endl;

  EXPECT_TRUE(true);
}
}  // namespace agenttest
