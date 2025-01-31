#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <string>
#include <utility>

namespace core {

class ErrorHandler {
public:
  static std::pair<int, std::string> ReturnGLFWError();
};

} // namespace core
#endif
