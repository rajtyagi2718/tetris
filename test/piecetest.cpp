#include "../include/piece.h"  // IPiece
#include <gtest/gtest.h>       // TEST EXPECT_TRUE
#include <iostream>            // cout endl
#include <memory>              // unique_ptr

namespace piecetest
{
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

TEST(PieceTest, Spawn)
{
  std::unique_ptr<Piece> P;
  for (int i = 0; i < 5; i++)
  {
    P = spawnpiece();
    std::cout << *P << std::endl;
  }
}
}  // namespace piecetest
