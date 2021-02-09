#include <iostream>
#include <sstream>

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

int main()
{
  enum Action {left, right, up, down};
  Action action{left};
  std::cout << "action\t " << action << std::endl;
  std::cout << "equality\t" << (action == 0) << std::endl;
  // uint64_t x = bittoint("111111111111"
  //                       "100000000001"
  //                       "111111111111"
  //                       "100000000001"
  //                       "111111111111");
  // std::cout << "board\n" << inttobit(x) << std::endl;

  // uint64_t y = x; 
  // y &= (y << 5);
  // std::cout << "board\n" << inttobit(y) << std::endl;
  // y &= (y << 2);
  // std::cout << "board\n" << inttobit(y) << std::endl;
  // y &= (y << 1);
  // std::cout << "board\n" << inttobit(y) << std::endl;
  // y &= (y << 1);
  // std::cout << "board\n" << inttobit(y) << std::endl;
}
