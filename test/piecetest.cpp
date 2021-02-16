#include "../include/piece.h"     // IPiece
#include "../include/bitboard.h"  // line
#include <gtest/gtest.h>          // TEST EXPECT_TRUE
#include <iostream>               // cout endl
#include <sstream>                // ostringstream
#include <vector>                 // vector
#include <memory>                 // unique_ptr make_unique
#include <random>                 // random_device mt19937 uniform_int_distribution
#include <algorithm>              // generate_n transform shuffle reverse
#include <iterator>               // back_inserter

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
  PieceTestFixture() : gen(rd()), 
                       op_distr(0, Operations_END-1), numops_distr(maxops, maxops) 
  {
  }

  int numtests = 1000;
  int maxops = 100;
  enum Operations {rotateright, up, left, right, down, rotateleft,
                   Operations_END};      
  std::random_device rd;
  std::mt19937 gen;
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

  int inverse (int op) { return Operations_END-1 - op; }
};

TEST_F(PieceTestFixture, OperationIdentities)
{
  std::unique_ptr<Piece> startpiece;
  
  for (int id = 0; id < PieceID_END; id++)
  {
    std::unique_ptr<Piece> startpiece = spawnpieceid(id);
    for (int test = 0; test < numtests; test++)
    {
      std::unique_ptr<Piece> piece = spawnpieceid(id);
      std::vector<int> opsvec {};
      std::vector<int> invopsvec {};  // inverse operations

      std::ostringstream oss {};
      oss << "test " << test << '\n' << *piece.get();

      int row = 0;
      for (int i = 0; i < numops_distr(gen); i++)
      {
        int op = op_distr(gen);
        // piece cannot go up when at top
        while ((op == 1) && (!row))
        {
          op = op_distr(gen);
        } 
        int invop = inverse(op);

        // check op and invop are actually inverses
        uint256_t curbigint = piece->getbigint();
        operate(op, piece);
        operate(invop, piece);
        ASSERT_EQ(curbigint, piece->getbigint()) << "bad inverse operation";

        operate(op, piece);

        // undo if piece hits border
        if (piece->getbigint() & bitboard::board)
        {
          operate(invop, piece);
        }
        // cache undo if legal operation
        else
        {
          opsvec.push_back(op); 
          invopsvec.push_back(invop);
          oss << "\nop " << op << '\n' << *piece.get();
          if (op == 4) { row++; }
          else if (op == 1) { row--; }
        }
      }

      // unwind stack
      std::reverse(invopsvec.begin(), invopsvec.end());
      for (auto invop : invopsvec)
      { 
        operate(invop, piece);
        oss << "\ninvop " << invop << '\n' << *piece.get();
      }

      oss << "\nexpected:\n" << *startpiece.get()
          << "\nactual:\n" << *piece.get();

      ASSERT_EQ(startpiece->getbigint(), piece->getbigint()) << oss.str();
    } 
  }
}
}  // namespace piecetest
