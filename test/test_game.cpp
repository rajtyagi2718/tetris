#include "../include/game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/graph.h"

int main()
{
  RandomAgent random_agent {};
  Board board {};
  Graph graph {};
  Game<RandomAgent> game {random_agent, board, graph, std::cout};
  game.play();
}
