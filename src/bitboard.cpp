#include "../include/bitboard.h"             // 
#include <boost/multiprecision/cpp_int.hpp>  // uint256_t export_bits import_bits
#include <ostream>                           // ostream 
#include <string>                            // string
#include <vector>                            // vector
#include <algorithm>                         // min
#include <iterator>                          // back_inserter
#include <iostream>

namespace bitboard
{
const int width  = 11;
const int length = 23;
const int offset = 2;

std::ostream& print(std::ostream& os, const uint256_t& bigint)
{
  std::vector<unsigned char> bitvec = uint256tobitvec(bigint);
  int curwidth = 11;
  for (auto it = bitvec.crbegin(); it != bitvec.crend(); it++)
  {
    os << ((*it) ? "o " : "  ");
    if (!(--curwidth))
    {
      os << '\n';
      curwidth = 11;
    }
  }
  return os; 
}

std::vector<unsigned char> uint256tobitvec(const uint256_t& bigint)
{
  std::vector<unsigned char> bitvec {};
  boost::multiprecision::export_bits(bigint, std::back_inserter(bitvec), 1);
  if (bitvec.size() >= offset)
  {
    bitvec.erase(bitvec.end() - offset, bitvec.end());
  }
  return bitvec;
}

int countbits(uint256_t bigint)
{
  int ret;
  for (ret = 0; bigint; ret++)
  {
    bigint &= bigint - 1;  // clear least significant bit
  }
  return ret;
}

const uint256_t board {internal::bitvectouint256(
  {1, 1,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1})};

const uint256_t block {internal::bitvectouint256(
  {0, 0,
   1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0})};

const uint256_t line {internal::bitvectouint256(
  {0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1})};

const uint256_t last {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1})};

const uint256_t tpiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t tpiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t tpiece2 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0})}; 

const uint256_t tpiece3 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t jpiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0})}; 

const uint256_t jpiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0})}; 

const uint256_t jpiece2 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0})}; 

const uint256_t jpiece3 {internal::bitvectouint256(
  {0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t zpiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0})}; 

const uint256_t zpiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t opiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0})}; 

const uint256_t spiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0})}; 

const uint256_t spiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0})}; 

const uint256_t lpiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0})}; 

const uint256_t lpiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})}; 

const uint256_t lpiece2 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
   0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0})}; 

const uint256_t lpiece3 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0})}; 

const uint256_t ipiece0 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0})}; 

const uint256_t ipiece1 {internal::bitvectouint256(
  {0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0})};                             

namespace internal
{
uint256_t bitvectouint256(std::vector<unsigned char> bitvec)
{
  uint256_t ret;
  // unsigned chunk_size = 1 bit
  // msv_first = false  i.e.  bigendian
  boost::multiprecision::import_bits(
    ret, bitvec.begin(), bitvec.end(), 1, false);

  return ret;
}  
}  // namespace internal
}  // namespace bitboard
