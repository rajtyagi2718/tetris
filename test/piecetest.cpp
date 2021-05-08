#include "../include/piece.h"     // 
#include "../include/bitboard.h"  //
#include <gtest/gtest.h>          //
#include <vector>                 // vector
#include <tuple>                  // tuple get tie
#include <memory>                 // unique_ptr make_unique
#include <random>                 // random_device mt19937 uniform_int_distribution

namespace piecetest
{
using boost::multiprecision::uint256_t;
using ::testing::TestWithParam;
using ::testing::Range;
using ::testing::Values;
using ::testing::Combine;

enum Operation {rotateleft, left, up, down, right, rotateright, Operation_END};      
class OperationBase
{
protected:
  OperationBase(int id)
    : piece{spawnpieceid(id)}, startint{piece->getbigint()}, msg{}
  {}

  std::unique_ptr<Piece> piece;
  uint256_t startint;
  std::ostringstream msg;

  void operate (int op)
  {
    switch (op)
    {
      case rotateright: piece->rotateright();  break;
      case up:          piece->up();           break;
      case left:        piece->left();         break;
      case right:       piece->right();        break;
      case down:        piece->down();         break;
      case rotateleft:  piece->rotateleft();   break;
      default: assert(false && "operation out of range [0, 5].");
    }
  }

  void invert (int op)
  {
    operate(Operation_END-1 - op);
  }
};

class OperationPrint
  : public TestWithParam<std::tuple<int, std::tuple<int, int>>>,
    public OperationBase
{
protected:
  OperationPrint()
    : OperationBase{std::get<0>(GetParam())} 
  { 
    std::tie(operation, operatenum) = std::get<1>(GetParam());
  }
 
  int operation; 
  int operatenum; 
};

TEST_P(OperationPrint, Identity)
{
  msg << *piece.get();
  for (int i = 0; i < operatenum; i++)
  {
    operate(operation);
    msg << '\n' << *piece.get();
  }
  for (int i = 0; i < operatenum; i++)
  {
    invert(operation);
    msg << '\n' << *piece.get();
  }
  ASSERT_EQ(startint, piece->getbigint()) << msg.str();
  std::cout << msg.str() << std::endl;
}

INSTANTIATE_TEST_CASE_P(PieceTest, OperationPrint, 
  Combine(Range(0, 7),
          Values(std::make_tuple<int, int>(rotateright, 4),
                 std::make_tuple<int, int>(rotateleft,  4),
                 std::make_tuple<int, int>(down,       19),
                 std::make_tuple<int, int>(left,        5),
                 std::make_tuple<int, int>(right,       4))));

class OperationStack
  : public TestWithParam<std::tuple<int, int>>,
    public OperationBase
{
protected:
  OperationStack()
    : OperationBase{std::get<0>(GetParam())}, operations{},
      gen(rd()), operation_distr(0, Operation_END-1), stacksize_distr(10, 300)
  {}

  std::vector<int> operations; 
  std::random_device rd;
  std::mt19937 gen;
  std::uniform_int_distribution<> operation_distr;  
  std::uniform_int_distribution<> stacksize_distr;  
};

TEST_P(OperationStack, Identities)
{
  // build stack
  int row = 0;
  for (int i = 0; i < stacksize_distr(gen); i++)
  {
    int op;
    // piece cannot go up when at top nor down when at bottom
    do
    {
      op = operation_distr(gen);
    } 
    while ((op == up && !row) || (op == down && piece->last()));

    // check identity: operate + invert
    uint256_t bigint = piece->getbigint();
    operate(op);
    invert(op);
    ASSERT_EQ(bigint, piece->getbigint()) << "bad inverse operation " << op;

    operate(op);
    ASSERT_TRUE(piece->valid());

    // undo if piece hits border
    if (piece->getbigint() & bitboard::board)
    {
      invert(op);
    }
    // cache operation if legal
    else
    {
      msg << "\noperation " << op;
      operations.push_back(op);
      msg << '\n' << *piece.get();
      if (op == down) { row++; }
      else if (op == up) { row--; }
    }
  }

  // unwind stack
  for (auto it = operations.crbegin(); it != operations.crend(); it++)
  { 
    msg << "\ninverse of " << *it;
    invert(*it);
    msg << '\n' << *piece.get();
  }

  msg << "\nexpected\n";
  bitboard::print(msg, startint);
  msg << "\nactual\n" << *piece.get();
  ASSERT_EQ(startint, piece->getbigint()) << msg.str();
}

INSTANTIATE_TEST_CASE_P(PieceTest, OperationStack, 
                        Combine(Range(0, 7), Range(0, 100)));
}  // namespace piecetest
