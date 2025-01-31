#ifndef MYAPP_HPP
#define MYAPP_HPP

#include "App/DemoGame/GameHandler/GameHandler.hpp"
#include "CoreBackend/GlfwHandler/GlfwHandler.hpp"
#include "CoreBackend/RenderHandler/RenderHandler.h"

namespace App {
class App {
private:
  testgame::GameHandler gameHandler;
  core::GlfwHandler glfwHandler;
  core::RenderHandler renderHandler;

public:
  App();
  ~App();

  void init();
  void mainLoop();
  void cleanup();
};
} // namespace App

#endif
