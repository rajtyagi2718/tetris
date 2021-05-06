#ifndef BITBOARD_H
#define BITBOARD_H

#include <boost/multiprecision/cpp_int.hpp>  // uint256_t
#include <vector>                            // vector

namespace bitboard
{
using boost::multiprecision::uint256_t;

extern const int width;
extern const int length;
extern const int offset;

std::ostream& print(std::ostream& os, const uint256_t& bigint);
std::vector<unsigned char> uint256tobitvec(const uint256_t& bigint);
int countbits(uint256_t bigint);

// BOARD
// 20x10 play field
// 23x11 bit mask = 253 bits

extern const uint256_t board;
extern const uint256_t block;
extern const uint256_t line;
extern const uint256_t last;
extern const uint256_t top;

extern const uint256_t tpiece0; 
extern const uint256_t tpiece1; 
extern const uint256_t tpiece2; 
extern const uint256_t tpiece3; 

extern const uint256_t jpiece0; 
extern const uint256_t jpiece1; 
extern const uint256_t jpiece2; 
extern const uint256_t jpiece3; 

extern const uint256_t zpiece0; 
extern const uint256_t zpiece1; 

extern const uint256_t opiece0; 

extern const uint256_t spiece0; 
extern const uint256_t spiece1; 

extern const uint256_t lpiece0; 
extern const uint256_t lpiece1; 
extern const uint256_t lpiece2; 
extern const uint256_t lpiece3; 

extern const uint256_t ipiece0; 
extern const uint256_t ipiece1; 

namespace internal
{
uint256_t bitvectouint256(std::vector<unsigned char> bitvec);
}  // namespace internal
}  // namespace bitboard

#endif  // BITBOARD_H
