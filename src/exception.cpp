#include "../include/exception.h"  // BoardIndexException
#include <sstream>                 // ostringstream
#include <string>                  // to_string

GameActionIndexException::GameActionIndexException(int index)
  : message{"agent action must be integer between [0, 4]."},
    index{index}
{
  message += " given action of " + std::to_string(index) + '.';

}

const char* GameActionIndexException::what() const noexcept
{
  return message.c_str(); 
}
