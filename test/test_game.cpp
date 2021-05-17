#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/graph.h"

void test_random_agent()
{
  std::cout << "test random agent" << std::endl;
  RandomAgent random_agent {};
  Board board {};
  Graph graph {};
  Game<RandomAgent> game {random_agent, board, graph, std::cout};
  game.play();
}

void test_search_agent()
{
  std::cout << "test search agent" << std::endl;
  SearchAgent search_agent {};
  Board board {};
  Graph graph {};
  Game<SearchAgent> game {search_agent, board, graph, std::cout};
  game.play();
}

int main()
{
  // test_random_agent();
  test_search_agent();
}
