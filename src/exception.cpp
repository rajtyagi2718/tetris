#include "../include/exception.h"  // BoardIndexException
#include <sstream>                 // ostringstream
#include <string>                  // to_string

SpawnPieceIndexException::SpawnPieceIndexException(int index)
  : message{"generated spawn index must be integer between [0, 6]."}, 
    index{index}
{
  message += " given index " + std::to_string(index) + '.';
}

const char* SpawnPieceIndexException::what() const noexcept
{
  return message.c_str(); 
}

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
