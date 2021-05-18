#include "../include/search.h"
#include "../include/bitboard.h"
#include <utility>

int main()
{
  std::cout << "constructor test" << std::endl;
  Search search {};

  std::vector<std::pair<uint256_t, int>> actions {};
  
  std::cout << "bfs test" << std::endl;
  search.run(bitboard::board,
             {bitboard::tpiece0, 0}, {bitboard::tpiece0, 0}, actions);
  std::cout << "actions: ";
  for (auto it = actions.crbegin(); it != actions.crend(); ++it)
  {
    auto [state, action] = *it;
    bitboard::print(std::cout, state);
    std::cout << '\t' << action << "\n\n";
  }
  std::cout << std::endl;
  actions.clear();
  search.run(bitboard::board,
             {bitboard::ipiece0, 6}, {bitboard::ipiece0, 6}, actions);
  std::cout << "actions: ";
  for (auto it = actions.crbegin(); it != actions.crend(); ++it)
  {
    auto [state, action] = *it;
    bitboard::print(std::cout, state);
    std::cout << '\t' << action << "\n\n";
  }
  std::cout << std::endl;
}
