#ifndef PIECE_H
#define PIECE_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector
#include <ostream>                           // ostream

namespace mp = boost::multiprecision;

class Piece
{
  public:
    mp::uint256_t getbigint();
    const mp::uint256_t& getbigint() const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& piece); 
    virtual void rotateright();
    virtual void rotateleft();
    void up();
    void down();
    void left();
    void right();

  protected:  
    // abstract class
    Piece(mp::uint256_t r0, mp::uint256_t r1, mp::uint256_t r2, 
          mp::uint256_t r3);  
    Piece(mp::uint256_t r);  

  private:
    int rot;
    std::vector<mp::uint256_t> rotations;
};

class IPiece : public Piece
{
  public:
    IPiece();
};

class OPiece : public Piece
{
  public:
    OPiece();
    void rotateright() override;
    void rotateleft() override;
};

class TPiece : public Piece
{
  public:
    TPiece();
};

class JPiece : public Piece
{
  public:
    JPiece();
};

class LPiece : public Piece
{
  public:
    LPiece();
};

class ZPiece : public Piece
{
  public:
    ZPiece();
};

class SPiece : public Piece
{
  public:
    SPiece();
};

#endif
