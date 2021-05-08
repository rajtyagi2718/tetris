#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"  // Board
#include "piece.h"  // Piece
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>   // vector
#include <unordered_map>  // unordered_map 
#include <set>      // set
#include <utility>  // pair
#include <memory>   // unique_ptr

using boost::multiprecision::uint256_t; 

class SearchGame
{
public:
  SearchGame();
  SearchGame(const SearchGame& searchgame);  // copy ctr for unique_ptr member
  void search(uint256_t boardint, int curpieceid, int nexpieceid,
              std::vector<std::pair<uint256_t, int>>& actions);

private:
  Board board; 
  std::unique_ptr<Piece> piece; 
  std::vector<double> weights;

  // afterstate -> state, action
  std::unordered_map<uint256_t, std::pair<uint256_t, int>> afterstates;
  std::set<uint256_t> terminalstates;
  
  void reset(uint256_t boardint, int pieceid);
  void bestactions(std::vector<std::pair<uint256_t, int>>& actions);
  void dfs();

  std::vector<int> legalactions();
  bool move(int action);
  void undo(int action);
  void forward(int action);
  void backward(int action);
  bool fall();
  void rise();

  double evaluate(uint256_t boardint);
};

#endif  // SEARCH_H
