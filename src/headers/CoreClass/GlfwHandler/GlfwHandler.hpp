#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>
#include <CoreClass/GlfwHandler/WindowHandler/WindowHandler.hpp>
//
#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/GlfwHandler/ImGuiHandler/ImGuiHandler.hpp>
#include <iostream>

namespace core
{

class GlfwHandler
{
private:
  static core::GlfwHandler *instance;

  GlfwHandler ();
  ~GlfwHandler ();

  GlfwHandler (GlfwHandler &other) = delete;
  void operator= (const GlfwHandler &) = delete;

  core::WindowHandler windowHandler;
  core::ImGuiHandler imguiHandler;

  void (*func) (GLFWwindow *window, GLfloat deltaTime) = nullptr;

  void setLoopVariables ();
  void swapBuffers ();
  void pollEvents ();
  void processInput (GLfloat deltaTime);

public:
  static core::GlfwHandler *createInstance ();
  void deleteInstance ();

  void startOfLoop (GLfloat deltaTime);
  void endOfLoop ();

  const core::Window returnMainWindow ();
  GLuint checkWindowShouldClose ();

  void initGlfw (std::string windowName, WindowType type, GLuint SCR_WIDTH,
                 GLuint SCR_HEIGHT);
  void terminateGlfw ();

  void setMainWindowMouseCallback (void (*func) (GLFWwindow *window,
                                                 double xposIn,
                                                 double yposIn));
  void setMainWindowFramebufferSizeCallback (void (*func) (GLFWwindow *window,
                                                           int width,
                                                           int height));
  void setMainWindowScrollCallback (void (*func) (GLFWwindow *window,
                                                  double xoffset,
                                                  double yoffset));
  void setMainWindowInputMode (int type, int mode);
  void setMainWindowInputProcessor (void (*func) (GLFWwindow *window,
                                                  GLfloat deltaTime));
};

} // namespace core

#endif
