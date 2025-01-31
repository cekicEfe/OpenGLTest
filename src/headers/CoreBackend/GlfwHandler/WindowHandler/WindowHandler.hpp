#ifndef WINDOWHANDLER
#define WINDOWHANDLER

#include <glad/glad.h>
//
#include <CoreBackend/GlfwHandler/WindowHandler/Window/Window.h>
#include <GLFW/glfw3.h>

namespace core {
class WindowHandler {
private:
  core::Window *mainWindow = nullptr;

public:
  WindowHandler();
  ~WindowHandler();

  void createMainWindow(std::string windowName, WindowType type,
                        GLuint SCR_WIDTH, GLuint SCR_HEIGHT);
  void destroyMainWindow();

  GLFWwindow *returnMainGLFWWindow();
  const core::Window &returnMainWindow() const;
};

}; // namespace core
#endif
