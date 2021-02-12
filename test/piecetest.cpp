#include "../include/piece.h"  // IPiece
#include <gtest/gtest.h>       // TEST EXPECT_TRUE
#include <iostream>            // cout

namespace piecetest
{
using namespace piece;

TEST(PieceTest, Test)
{
  IPiece I{};
  std::cout << "[          ] I-Piece\n" << I << std::endl; 
  I.rotateright();
  std::cout << "[          ] I-Piece rotateright\n" << I << std::endl; 
  I.down();
  std::cout << "[          ] I-Piece down\n" << I << std::endl; 
  EXPECT_TRUE(true);
}
}  // namespace piecetest
