#ifndef ERRORHANDLER_HPP
#define ERRORHANDLER_HPP

#include <GLFW/glfw3.h>
#include <string>
#include <utility>

namespace core {

class ErrorHandler {
public:
  static std::pair<int, std::string> ReturnGLFWError();
  static GLenum getOpenglError(const char *file, int line);
};

} // namespace core
#endif
