#include "App/App.hpp"
#include "imguiFileExplorer/imfilebrowser.h"
#include <imgui.h>

App::App::App() {}

App::App::~App() {}

void App::App::init() {
  this->glfwHandler.inputHandler.setFramebufferSizeCallbackFun(
      this->gameHandler.defaultFramebufferSizeCallback);
  this->glfwHandler.inputHandler.setCursorCallbackFun(
      this->gameHandler.mouse_callback);
  this->glfwHandler.inputHandler.setScrollCallback(
      this->gameHandler.scrollCallback);
  this->glfwHandler.inputHandler.setInputMode(GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  // function order matters
  // demo creates models that rely on glfw first
  // so init glfw first
  this->glfwHandler.initGlfwHandler("Test", 1920, 1080);
  this->gameHandler.demoInit();
}

void App::App::mainLoop() {
  while (!this->glfwHandler.checkWindowShouldClose()) {
    this->glfwHandler.beginLoop();
    this->gameHandler.demoMainLoop(glfwHandler.returnMainWindow());
    this->glfwHandler.endLoop();
  }
}

void App::App::cleanup() {
  this->glfwHandler.cleanupGlfwHandler();
  this->gameHandler.demoCleanup();
}
