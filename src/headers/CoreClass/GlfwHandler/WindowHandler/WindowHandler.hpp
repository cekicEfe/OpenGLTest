#ifndef WINDOWHANDLER
#define WINDOWHANDLER

#include <glad/glad.h>
//
#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>
#include <GLFW/glfw3.h>
#include <memory>

namespace core
{
class WindowHandler
{
private:
  WindowHandler ();
  ~WindowHandler ();

  WindowHandler (WindowHandler &other) = delete;
  void operator= (const WindowHandler &) = delete;

  core::Window mainWindow;

  void createMainWindow (std::string windowName, WindowType type,
                         GLuint SCR_WIDTH, GLuint SCR_HEIGHT);
  void destroyMainWindow ();
  GLFWwindow *returnMainGLFWWindow ();
  const core::Window &returnMainWindow ();

public:
  friend class core::GlfwHandler;
};

};
#endif
