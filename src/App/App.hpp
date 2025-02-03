#ifndef MYAPP_HPP
#define MYAPP_HPP

#include "App/DemoGame/GameHandler/GameHandler.hpp"
#include "CoreBackend/GlfwHandler/GlfwHandler.hpp"
#include "CoreBackend/RenderHandler/RenderHandler.h"

namespace App {
class App {
private:
  testgame::GameHandler gameHandler;
  // core::RenderHandler renderHandler;
  core::GlfwHandler glfwHandler;

public:
  App();
  ~App();

  void init();
  void mainLoop();
  void cleanup();
};
} // namespace App

#endif
