#include "ErrorHandler.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory.h>
#include <utility>

std::pair<int, std::string> core::ErrorHandler::ReturnGLFWError() {
  const char *description;
  int code = glfwGetError(&description);

  if (description)
    std::cout << "Error Code :" << code << "\n"
              << "Error Name :" << description << std::endl;
  std::string newString(description);

  delete description;

  return std::pair<int, std::string>(code, newString);
};
