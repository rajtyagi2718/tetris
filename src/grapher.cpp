#include "../include/bitboard.h"
#include "../include/piece.h"
#include "../include/grapher.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <fstream>                           // ofstream
#include <algorithm>                         // sort
#include <iostream>

using boost::multiprecision::uint256_t; 

Grapher::Grapher()
  : board{}, piece{}, states{}, afterstates{}
{
}

void Grapher::dfs()
{
  for (int id = 0; id < PieceId_END; id++)
  {
    piece = spawn_piece(id);
    tops.clear();
    enumerate_tops();

    afterstates.clear();
    states.clear();
    uint256_t state = piece->get_state();

    explore(state);

    std::sort(states.begin(), states.end());
    write_afterstates(id);
  }
}

void Grapher::enumerate_tops()
{
  for (auto state : piece->get_rotations())
  {
    tops.insert(state);
    uint256_t afterstate = state;
    while (board.is_valid(afterstate))
    {
      afterstate = left_state(afterstate);
      assert(!tops.count(afterstate));
      tops.insert(afterstate);
    }
    afterstate = state;
    while (board.is_valid(afterstate))
    {
      afterstate = right_state(afterstate);
      assert(!tops.count(afterstate));
      tops.insert(afterstate);
    }
  } 
}

void Grapher::explore(uint256_t state)
{
  assert(bitboard::countbits(state) == 4);
  states.push_back(state);
  afterstates[state];  // initialize to zeros
  uint256_t afterstate = 0;

  if (!piece->is_bottom())
  {
    forward(down); 
    afterstate = piece->get_state();
    assert(bitboard::countbits(afterstate) == 4);
    if (!afterstates.count(afterstate))
    {
      explore(afterstate);
    }
    afterstates[state][down] = afterstate; 
    backward(down);
    assert(state == piece->get_state());
  }
  else
  {
    explore_floor(state);
  }

  for (int action = down+1; action < up; action++)
  {
    forward(action); 
    afterstate = piece->get_state();
    afterstates[state][action] = afterstate; 
    assert(bitboard::countbits(afterstate) == 4);
    if (board.is_valid(afterstate))
    {
      if (!afterstates.count(afterstate))
      {
        explore(afterstate);
      }
    }
    else
    {
      afterstates[afterstate][Action_END - action - 1] = state;
      states.push_back(afterstate);
    }
    backward(action);
    assert(state == piece->get_state());
  }

  if (!tops.count(state))
  {
    forward(up); 
    afterstate = piece->get_state();
    assert(bitboard::countbits(afterstate) == 4);
    if (!afterstates.count(afterstate))
    {
      explore(afterstate);
    }
    afterstates[state][up] = afterstate; 
    backward(up);
    assert(state == piece->get_state());
  }
}

void Grapher::explore_floor(uint256_t state)
{
  uint256_t afterstate = down_state(state);  
  assert(bitboard::countbits(afterstate) == 4);
  afterstates[state][down] = afterstate; 
  afterstates[afterstate][up] = state;
  states.push_back(afterstate);
}

void Grapher::forward(int action)
{
  switch (action)
  {
    case down:         piece->down();          break;
    case rotate_left:  piece->rotate_left();   break;
    case left:         piece->left();          break;
    case right:        piece->right();         break;
    case rotate_right: piece->rotate_right();  break;
    case up:           piece->up();            break;
    default: assert(false && "forward action out of range [0, 5].");
  }
  assert(piece->is_valid());
}

void Grapher::backward(int action)
{
  forward(Action_END - action - 1); 
  assert(piece->is_valid());
}

void Grapher::write_afterstates(int id)
{
  std::string file_name {"build/afterstates_"};
  file_name += std::to_string(id) + ".txt";
  std::ofstream file {file_name};
 
  if (file.is_open())
  {
    for (const auto& state : states)
    {
      file << state;
      for (const auto& afterstate : afterstates[state])
      {
        file << ' ' << afterstate;
      } 
      file << '\n';
    }
    file.close();
  }
  else
  {
    assert(false && "failed to open afterstates file");
  } 
  std::cout << file_name << " write complete." << std::endl;
}
