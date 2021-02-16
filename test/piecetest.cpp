#include "../include/piece.h"  // IPiece
#include <gtest/gtest.h>       // TEST EXPECT_TRUE
#include <iostream>            // cout endl
#include <vector>              // vector
#include <memory>              // unique_ptr make_unique
#include <random>              // random_device mt19937 uniform_int_distribution
#include <algorithm>           // generate_n transform shuffle
#include <iterator>            // back_inserter

namespace piecetest
{
TEST(PieceTest, PrintRotateRightLeft)
{
  std::unique_ptr<Piece> piece = spawnpiece();
  std::cout << *piece.get() << std::endl;
  for (int i = 0; i < 4; i++)
  {
    piece->rotateright();
    std::cout << *piece.get() << std::endl;
  }
  for (int i = 0; i < 4; i++)
  {
    piece->rotateleft();
    std::cout << *piece.get() << std::endl;
  }
}

TEST(PieceTest, PrintDownUp)
{
  std::unique_ptr<Piece> piece = spawnpiece();
  std::cout << *piece.get() << std::endl;
  for (int i = 0; i < 20; i++)
  {
    piece->down();
    std::cout << *piece.get() << std::endl;
  }
  for (int i = 0; i < 20; i++)
  {
    piece->up();
    std::cout << *piece.get() << std::endl;
  }
}

TEST(PieceTest, PrintLeftRight)
{
  std::unique_ptr<Piece> piece = spawnpiece();
  std::cout << *piece.get() << std::endl;
  for (int i = 0; i < 4; i++)
  {
    piece->left();
    std::cout << *piece.get() << std::endl;
  }
  for (int i = 0; i < 8; i++)
  {
    piece->right();
    std::cout << *piece.get() << std::endl;
  }
  for (int i = 0; i < 4; i++)
  {
    piece->left();
    std::cout << *piece.get() << std::endl;
  }
}

// TODO test fixture, debug

class PieceTestFixture : public ::testing::Test
{
public:
  PieceTestFixture() : op_distr(0, Operations_END-1), numops_distr(1, numops) {}

  int numtests = 1000;
  int numops = 100;
  enum Operations {rotateright, up, left, right, down, rotateleft,
                   Operations_END};      
  std::mt19937 gen(std::random_device());
  std::uniform_int_distribution<> op_distr;  
  std::uniform_int_distribution<> numops_distr;  
  
  void operate (int op, const std::unique_ptr<Piece>& piece)
  {
    switch (op)
    {
      case rotateright: piece->rotateright();  break;
      case up:          piece->up();           break;
      case left:        piece->left();         break;
      case right:       piece->right();        break;
      case down:        piece->down();         break;
      case rotateleft:  piece->rotateleft();   break;
      default: assert(false && "oppiece op out of range [0, 5].");
    }
  }
};

TEST_F(PieceTestFixture, OperationIdentities)
{
  std::vector<int> opsvec;
  std::vector<int> invopsvec;  // inverse operations
  std::unique_ptr<Piece> startpiece;
  std::unique_ptr<Piece> piece;
  
  for (int id = 0; id < PieceID_END; id++)
  {
    startpiece = spawnpieceid(id);
    for (int test = 0; test < numtests; test++)
    {
      piece = spawnpieceid(id);
      opsvec.clear();
      invopsvec.clear();      

      // fill opsvec with random operations of random length
      std::generate_n(std::back_inserter(opsvec), numops_distr(gen), 
                      []() { return op_distr(gen); });
      // fill invopsvec with inverse operations of those in opsvec
      std::transform(opsvec.cbegin(), opsvec.cend(), 
                     std::back_inserter(invopsvec),
                     [](const int& x) { return Operations_END - x; });
      // all operations commutative
      std::shuffle(invopsvec.begin(), invopsvec.end(), gen);

      for (auto op : opsvec) { operate(op, piece); }
      for (auto op : invopsvec) { operate(op, piece); }

      ASSERT_EQ(startpiece->getbigint(), piece->getbigint());
    } 
  }
}
}  // namespace piecetest
