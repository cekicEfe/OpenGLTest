#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <GLFW/glfw3.h>

namespace core {

class InputHandler {
private:
  int inputMode = GLFW_CURSOR;
  int inputValue = GLFW_CURSOR_NORMAL;

  // GLFWcursorposfun
  void (*cursorCallback)(GLFWwindow *window, double xposIn,
                         double yposIn) = nullptr;
  // GLFWframebuffersizefun
  void (*framebufferSizeCallback)(GLFWwindow *window, int width,
                                  int height) = nullptr;
  // GLFWscrollfun
  void (*scrollCallback)(GLFWwindow *window, double xoffset,
                         double yoffset) = nullptr;

public:
  InputHandler();
  ~InputHandler();

  void setCursorCallbackFun(void (*cursorCallback)(GLFWwindow *window,
                                                   double xposIn,
                                                   double yposIn));
  void setFramebufferSizeCallbackFun(void (*framebufferSizeCallback)(
      GLFWwindow *window, int width, int height));

  void setScrollCallback(void (*scrollCallback)(GLFWwindow *window,
                                                double xoffset,
                                                double yoffset));
  void setInputMode(int inputMode, int inputValue);
  void setupCallbacks(GLFWwindow *window);
};

} // namespace core

#endif
