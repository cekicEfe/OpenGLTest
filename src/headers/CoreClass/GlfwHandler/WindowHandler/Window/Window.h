#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
//
#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <iostream>

namespace core
{

enum WindowType
{
  FULL_SCREEN,
  WINDOWED
};

class Window
{
private:
  Window (Window &other) = delete;
  void operator= (const Window &) = delete;

  std::string windowName;
  WindowType type;
  GLuint SCR_WIDTH;
  GLuint SCR_HEIGHT;

  GLFWwindow *window;
  GLuint windowIsSet;

  void createWindow ();
  void destroyWindow ();
  GLFWwindow *returnGLFWWindow ();

public:
  Window ();
  Window (std::string windowName, WindowType type, GLuint SCR_WIDTH,
          GLuint SCR_HEIGHT);
  ~Window ();

  const GLuint &getScrWidth () const;
  const GLuint &getScrHeight () const;

  friend class core::WindowHandler;
};

}

#endif
