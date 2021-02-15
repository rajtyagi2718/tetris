#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>  // exception
#include <string>     // string

class BoardIndexException : public std::exception
{
  public:
    BoardIndexException(int index);
    const char* what() const noexcept override;

  private:
    std::string message;
    int index;
};

class SpawnPieceIndexException : public std::exception
{
  public:
    SpawnPieceIndexException(int index);
    const char* what() const noexcept override;

  private:
    std::string message;
    int index;
};

class GameActionIndexException : public std::exception
{
  public:
    GameActionIndexException(int index);
    const char* what() const noexcept override;

  private:
    std::string message;
    int index;
};

#endif  // EXECPTION_H
