#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
//
#include <iostream>

namespace core {

enum WindowType { FULL_SCREEN, WINDOWED };

class Window {
private:
  std::string windowName;
  WindowType type;
  GLuint SCR_WIDTH;
  GLuint SCR_HEIGHT;

  GLFWwindow *window = nullptr;
  GLuint windowIsSet = 0;

  void createWindow();
  void destroyWindow();

public:
  Window(std::string windowName, WindowType type, GLuint SCR_WIDTH,
         GLuint SCR_HEIGHT);
  ~Window();

  const GLuint &getScrWidth() const;
  const GLuint &getScrHeight() const;
  GLFWwindow *returnGLFWWindow();
};

} // namespace core

#endif
