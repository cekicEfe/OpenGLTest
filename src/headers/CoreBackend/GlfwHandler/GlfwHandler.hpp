#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <CoreBackend/GlfwHandler/WindowHandler/Window/Window.h>
//
#include <CoreBackend/GlfwHandler/InputCallbackHandler/InputHandler.hpp>
#include <CoreBackend/GlfwHandler/WindowHandler/WindowHandler.hpp>
//
#include <CoreBackend/ErrorHandler/ErrorHandler.hpp>
#include <CoreBackend/GlfwHandler/ImGuiHandler/ImGuiHandler.hpp>
#include <iostream>

namespace core
{

class GlfwHandler
{
private:
  core::WindowHandler windowHandler;
  core::ImGuiHandler imguiHandler;

  void initImGui ();
  void initLoopImGui ();
  void renderImGui ();
  void terminateImGui ();

  void setLoopVariables ();
  void swapBuffers ();
  void pollEvents ();

public:
  GlfwHandler ();
  ~GlfwHandler ();

  core::InputHandler inputHandler;

  void initGlfwHandler (std::string windowName, GLuint SCR_WIDTH,
                        GLuint SCR_HEIGHT);
  GLuint checkWindowShouldClose ();
  void beginLoop ();

  const core::Window &returnMainWindow ();

  void endLoop ();
  void cleanupGlfwHandler ();
};

} // namespace core

#endif
