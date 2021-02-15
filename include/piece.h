#ifndef PIECE_H
#define PIECE_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector
#include <ostream>                           // ostream
#include <memory>                            // unique_ptr

using boost::multiprecision::uint256_t;

class Piece
{
  public:
    uint256_t getbigint();
    const uint256_t& getbigint() const;
    int getid() const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& piece); 
    virtual void rotateright();
    virtual void rotateleft();
    void up();
    void down();
    void left();
    void right();
    bool top() const;

  protected:  
    // abstract class
    Piece(int id, uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3);  
    Piece(int id, uint256_t r);  

  private:
    int rot;
    int id;
    std::vector<uint256_t> rotations;
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

enum PieceID {ipiece, opiece, tpiece, jpiece, lpiece, zpiece, spiece, 
              PieceID_END};

std::unique_ptr<Piece> spawnpiece();

#endif  // PIECE_H
