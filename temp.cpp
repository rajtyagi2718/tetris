#include "temp.h"
#include <iostream>
#include <sstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <iomanip>
#include <vector>
#include <iterator>
#include <string>
#include <ostream>

using uint256_t = boost::multiprecision::uint256_t;

std::string inttobit(uint64_t bigint)
{
  std::ostringstream oss {};
  int width = 12;
  while (bigint)
  {
    oss << (bigint & 1) ? '1' : '0';
    bigint >>= 1;

    width -= 1;
    if (!width)
    {
      oss << '\n';
      width = 12;
    }
  }

  return oss.str();
} 

uint64_t bittoint(const std::string& bitstr)
{
  uint64_t res = 0;
  for (auto itr = bitstr.crbegin(); itr != bitstr.crend(); itr++)
  {
    // last '1' of bitstr = most significant bit of int
    res <<= 1;
    if (*itr == '1')
    {
      res += 1;
    }
  }

  return res;
}


uint256_t setints(std::vector<unsigned char> bits)
{

  uint256_t ret;
  import_bits(ret, bits.begin(), bits.end(), 1, false);

  return ret;
}

namespace temp
{
  uint256_t x = 1;
  const uint256_t line = setints({0, 0, 1, 0, 0, 1, 1});
}

std::ostream& print(std::ostream& os, uint256_t bigint)
{
  std::vector<unsigned char> bitvec {};
  export_bits(bigint, std::back_inserter(bitvec), 1);

  int curwidth = 11;
  for (const auto& bit : bitvec)
  {
    os << bool(bit) << ' ';
    if (!(--curwidth))
    {
      os << '\n';
      curwidth = 11;
    }
  }

  return os; 
}

int main()
{
  using boost::multiprecision::cpp_int;
  // Create a cpp_int with just a couple of bits set:
  uint256_t i;
  bit_set(i, 2); // set the 5000'th bit
  bit_set(i, 5);
  bit_set(i, 6);
  // print int
  std::cout << i << std::endl;

  // export into 8-bit unsigned values, most significant bit first:
  std::vector<unsigned char> v;
  export_bits(i, std::back_inserter(v), 1);
  // print vector
  for (const auto& x: v)
  {
    std::cout << bool(x) << " ";
  }
  std::cout << std::endl;

  print(std::cout, i);
  std::cout << std::endl;

  // // import back again, and check for equality:
  // cpp_int j;
  // import_bits(j, v.begin(), v.end(), 1);
  // assert(i == j);

  // std::vector<unsigned char> vec {0, 0, 1, 0, 0, 1, 1};
  // cpp_int x;
  // import_bits(x, vec.begin(), vec.end(), 1, false);
  // assert(x == 100);


  // // define const uint256_t
  // using uint256_t = boost::multiprecision::uint256_t;
  // uint256_t {
}
