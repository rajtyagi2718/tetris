#ifndef GRAPH_H
#define GRAPH_H

#include "bitboard.h"
#include "board.h"
#include "ids.h"    // Action PieceId
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <map>
#include <vector>
#include <random>   // random_device mt19937 uniform_int_distribution
#include <utility>  // pair

// dynamically create piece (state, id) pairs 
// quickly map (state, id, action) triples to adjacent states
// read graph from file

using boost::multiprecision::uint256_t;

class Graph
{
public:
  Graph();
  std::pair<uint256_t, int> spawn();
  void move(std::pair<uint256_t, int>& piece, int action);
  void undo(std::pair<uint256_t, int>& piece, int action);

  uint256_t get_after_state(uint256_t state, int id, int action);
  uint256_t get_before_state(uint256_t state, int id, int action);

private:
  std::array<std::map<uint256_t, std::array<uint256_t, Action_END>>, 
             PieceId_END> after_states;
  std::vector<uint256_t> spawn_states;

  std::random_device rd; 
  std::mt19937 gen;
  std::uniform_int_distribution<> distrib;
};

#endif  // GRAPH_H
