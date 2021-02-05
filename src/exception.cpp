#include "../include/exception.h"
#include <sstream>  // ostringstream
#include <string>  // to_string

BoardIndexException::BoardIndexException(int index)
  : index{index}
{
  message = "move direc must be either: 0, 1, 2, 3.";
  message += " given direc of " + std::to_string(index) + '.';

}

const char* BoardIndexException::what() const noexcept
{
  return message.c_str(); 
}
