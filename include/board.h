#ifndef BOARD_H
#define BOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream

namespace board
{
using boost::multiprecision::uint256_t;

class Board
{
  public:
    Board();
    uint256_t getbigint();
    const uint256_t& getbigint() const;
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    bool checkpiece(const uint256_t& piece);  
    void addpiece(const uint256_t& piece);  
    bool trypiece(const uint256_t& piece);  
    void rempiece(const uint256_t& piece);  
    void clearlines();

  private:
    uint256_t bigint;
};
}  // namespace board

#endif  // BOARD_H
