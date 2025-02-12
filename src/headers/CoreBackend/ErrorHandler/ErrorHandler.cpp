#include <glad/glad.h>
//
#include "ErrorHandler.hpp"
//
#include <GL/gl.h>
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

GLenum core::ErrorHandler::getOpenglError(const char *file, int line) {
  GLenum error_code;
  while ((error_code = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (error_code) {
    case GL_INVALID_ENUM:
      error = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      error = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      error = "INVALID_OPERATION";
      break;
    case GL_STACK_OVERFLOW:
      error = "STACK_OVERFLOW";
      break;
    case GL_STACK_UNDERFLOW:
      error = "STACK_UNDERFLOW";
      break;
    case GL_OUT_OF_MEMORY:
      error = "OUT_OF_MEMORY";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      error = "INVALID_FRAMEBUFFER_OPERATION";
      break;
    }
    std::cout << error << " | " << file << " (" << line << ")" << std::endl;
  }
  return error_code;
}
