#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"  // Board
#include "piece.h"  // Piece
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>   // vector
#include <set>      // set
#include <map>      // map
#include <utility>  // pair
#include <memory>   // unique_ptr

using boost::multiprecision::uint256_t; 

class SearchGame
{
public:
  SearchGame();
  SearchGame(const SearchGame& searchgame);  // copy ctr for unique_ptr member
  void reset(uint256_t boardint, int pieceid);
  void search();
  void bestactions(std::vector<int>& actions);

private:
  Board board; 
  std::unique_ptr<Piece> piece; 
  std::vector<std::vector<int>> paths;
  std::vector<uint256_t> states;
  std::set<uint256_t> cache;
  
  // std::vector<std::pair<int, int>> stack;  // {count, action}
  // std::vector<std::map<uint256_t, int>> indices;  // [pieceid][state] -> index
  // std::vector<std::vector<uint256_t>> states;  // [pieceid][index] -> state

  std::vector<int> legalactions();
  bool move(int action);
  void undo(int action);
  void forward(int action);
  void backward(int action);
  bool fall();
  void rise();
};

#endif  // SEARCH_H
