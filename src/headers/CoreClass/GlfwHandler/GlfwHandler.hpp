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
  GlfwHandler (GlfwHandler &other) = delete;
  void operator= (const GlfwHandler &) = delete;

  core::WindowHandler windowHandler;
  core::ImGuiHandler imguiHandler;

  void (*inputProcessor) (GLFWwindow *window, GLfloat deltaTime) = nullptr;

  void setLoopVariables ();
  void swapBuffers ();
  void pollEvents ();
  void processInput (GLfloat deltaTime);
  void terminateGlfw ();

public:
  GlfwHandler ();
  /*
   *DEconstructor calls terminateGlfw !!!
   */
  ~GlfwHandler ();

  void initGlfw (std::string windowName, WindowType type, GLuint SCR_WIDTH,
                 GLuint SCR_HEIGHT, int inputMode, int inputValue,
                 void (*frameSizeCallback) (GLFWwindow *window, int width,
                                            int height)
                 = nullptr,
                 void (*mouseCallback) (GLFWwindow *window, double xposIn,
                                        double yposIn)
                 = nullptr,
                 void (*scrollCallback) (GLFWwindow *window, double xoffset,
                                         double yoffset)
                 = nullptr,
                 void (*inputProcessor) (GLFWwindow *window, GLfloat deltaTime)
                 = nullptr);

  void startOfLoop (GLfloat deltaTime);
  void endOfLoop ();

  GLuint checkWindowShouldClose ();
  const core::Window &returnMainWindow () const;

  void setMainWindowMouseCallback (void (*func) (GLFWwindow *window,
                                                 double xposIn,
                                                 double yposIn));
  void setMainWindowFramebufferSizeCallback (void (*func) (GLFWwindow *window,
                                                           int width,
                                                           int height));
  void setMainWindowScrollCallback (void (*func) (GLFWwindow *window,
                                                  double xoffset,
                                                  double yoffset));
  void setMainWindowInputMode (int mode, int value);
  void setMainWindowInputProcessor (void (*func) (GLFWwindow *window,
                                                  GLfloat deltaTime));
};

} // namespace core

#endif
