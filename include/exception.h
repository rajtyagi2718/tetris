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

#endif
