#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include "CoreClass/CoreClassPreDec.h"
#include <string>
#include <utility>

namespace core
{

class ErrorHandler
{
public:
  static std::pair<int, std::string> ReturnOpenglError ();
  friend int ::main (int, char **);
};

} // namespace core
#endif
