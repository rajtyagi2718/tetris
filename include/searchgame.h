#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"  // Board
#include "piece.h"  // Piece
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>   // vector
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
  std::vector<int> legalactions();
  bool move(int action);
  void undo(int action);
  void forward(int action);
  void backward(int action);
  bool fall();
  void rise();
};

#endif  // SEARCH_H
