#ifndef PIECE_H
#define PIECE_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector
#include <ostream>                           // ostream
#include <memory>                            // unique_ptr
#include <random>                            // random_device mt19937

using boost::multiprecision::uint256_t;

class Piece
{
public:
  uint256_t getbigint();
  const uint256_t& getbigint() const;
  int getid() const;
  unsigned int getrot() const;
  friend std::ostream& operator<<(std::ostream& os, const Piece& piece); 
  void rotateright();
  void rotateleft();
  void up();
  void down();
  void left();
  void right();
  bool top() const;
  bool last() const;
  bool valid() const;
  std::ostream& printrotations(std::ostream& os) const;

protected:  
  // abstract class
  Piece(int id, uint256_t r0, uint256_t r1, uint256_t r2, uint256_t r3);  
  Piece(int id, uint256_t r0, uint256_t r1);  
  Piece(int id, uint256_t r);  

private:
  int id;
  unsigned int rot;  // getter %
  unsigned int numrot;
  std::vector<uint256_t> rotations;
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

class ZPiece : public Piece
{
public:
  ZPiece();
};

class OPiece : public Piece
{
public:
  OPiece();
};

class SPiece : public Piece
{
public:
  SPiece();
};

class LPiece : public Piece
{
public:
  LPiece();
};

class IPiece : public Piece
{
public:
  IPiece();
};


enum PieceID {tpiece, jpiece, zpiece, opiece, spiece, lpiece, ipiece,
              PieceID_END};

std::unique_ptr<Piece> spawnpiece();

std::unique_ptr<Piece> spawnpieceid(int id);


class SevenBagRandomizer
{
public:
  SevenBagRandomizer();
  std::unique_ptr<Piece> spawnpiece();

private:
  std::vector<int> ids;
  std::random_device rd; 
  std::mt19937 gen;
  std::vector<int>::const_iterator idsit;

  void reset();
};

#endif  // PIECE_H
