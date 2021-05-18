#include "../include/graphics_game.h"
#include "../include/agent.h"
#include "../include/board.h"
#include "../include/graph.h"

int main()
{
  SearchAgent agent {};
  Board board {};
  Graph graph {};
  GraphicsGame<SearchAgent> game{agent, board, graph, std::cout};
  game.play();
}
