#include "../include/search.h"
#include "../include/bitboard.h"
#include <utility>

int main()
{
  std::cout << "constructor test" << std::endl;
  Search search {};

  std::vector<int> actions {};
  
  std::cout << "bfs test" << std::endl;
  search.run(bitboard::board,
             {bitboard::tpiece0, 0}, {bitboard::tpiece0, 0}, actions);
  std::cout << "actions: ";
  for (auto action : actions)
  {
    std::cout << action << ' ';
  }
  std::cout << std::endl;
  actions.clear();
  search.run(bitboard::board,
             {bitboard::ipiece0, 6}, {bitboard::ipiece0, 6}, actions);
  std::cout << "actions: ";
  for (auto action : actions)
  {
    std::cout << action << ' ';
  }
  std::cout << std::endl;
}
