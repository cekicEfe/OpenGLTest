#include "WindowHandler.hpp"
#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include <stdexcept>

core::WindowHandler::WindowHandler() {}

core::WindowHandler::~WindowHandler() {}

void core::WindowHandler::createMainWindow(std::string windowName,
                                           WindowType type, GLuint SCR_WIDTH,
                                           GLuint SCR_HEIGHT) {
  if (this->mainWindow == nullptr)
    this->mainWindow =
        new core::Window(windowName, type, SCR_WIDTH, SCR_HEIGHT);
  else
    throw std::runtime_error("Tried to create mainWindow again at "
                             "core::WindowHandler::createMainWindow");
}

void core::WindowHandler::destroyMainWindow() {
  if (this->mainWindow != nullptr)
    delete this->mainWindow;
  else if (this->mainWindow == nullptr)
    throw std::runtime_error("Tried to delete mainWindow again "
                             "core::WindowHandler::createMainWindow");
}
GLFWwindow *core::WindowHandler::returnMainGLFWWindow() {
  return this->mainWindow->returnGLFWWindow();
}

const core::Window &core::WindowHandler::returnMainWindow() const {
  return *this->mainWindow;
}
