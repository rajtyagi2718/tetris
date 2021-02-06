#ifndef PIECE_H
#define PIECE_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector
#include <ostream>                           // ostream

namespace mp = boost::multiprecision;

class Piece
{
  public:
    mp::uint256_t getbigint() const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& piece); 

  protected:  
    // abstract class
    Piece(mp::uint256_t r0, mp::uint256_t r1, mp::uint256_t r2, 
          mp::uint256_t r3);  
    int rot;
    const std::vector<mp::uint256_t> rotations;
};

class IPiece : Piece
{
  public:
    IPiece();
};

#endif
