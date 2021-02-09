#ifndef BOARD_H
#define BOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <ostream>                           // ostream

namespace mp = boost::multiprecision;

class Board
{
  public:
    Board();
    mp::uint256_t getbigint();
    const mp::uint256_t& getbigint() const;
    friend std::ostream& operator<<(std::ostream& os, const Board& board);
    bool checkpiece(const mp::uint256_t& piece);  
    void addpiece(const mp::uint256_t& piece);  
    bool trypiece(const mp::uint256_t& piece);  
    void rempiece(const mp::uint256_t& piece);  
    void clearlines();

  private:
    mp::uint256_t bigint;
};

#endif
