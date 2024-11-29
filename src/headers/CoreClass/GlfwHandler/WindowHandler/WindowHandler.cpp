#include "WindowHandler.hpp"

core::WindowHandler::WindowHandler ()
{
}

core::WindowHandler::~WindowHandler ()
{
}

void
core::WindowHandler::createMainWindow (std::string windowName, WindowType type,
                                       GLuint SCR_WIDTH, GLuint SCR_HEIGHT)
{
  this->mainWindow.windowName = windowName;
  this->mainWindow.type = type;
  this->mainWindow.SCR_HEIGHT = SCR_HEIGHT;
  this->mainWindow.SCR_WIDTH = SCR_WIDTH;

  this->mainWindow.window = nullptr;
  this->mainWindow.windowIsSet = 0;

  this->mainWindow.createWindow ();
}

void
core::WindowHandler::destroyMainWindow ()
{
  this->mainWindow.destroyWindow ();
}

GLFWwindow *
core::WindowHandler::returnMainGLFWWindow ()
{
  return this->mainWindow.returnGLFWWindow ();
}

const core::Window &
core::WindowHandler::returnMainWindow ()
{

  return this->mainWindow;
}
