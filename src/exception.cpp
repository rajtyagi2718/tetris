#include "../include/exception.h"  // BoardIndexException
#include <sstream>                 // ostringstream
#include <string>                  // to_string

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

GameActionIndexException::GameActionIndexException(int index)
  : index{index}
{
  message = "agent action must be integer between [0, 4].";
  message += " given action of " + std::to_string(index) + '.';

}

const char* GameActionIndexException::what() const noexcept
{
  return message.c_str(); 
}
