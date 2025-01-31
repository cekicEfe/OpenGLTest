#include "App/App.hpp"
#include "GraphicsBackend/Model/Model.h"

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

  this->glfwHandler.initGlfwHandler("TEST", 1000, 1000);
  this->gameHandler.initDemo();
}

void App::App::mainLoop() {
  while (!this->glfwHandler.checkWindowShouldClose()) {
    static GLfloat deltaTime = this->gameHandler.calculateDeltaTime();
    this->glfwHandler.beginLoop();
    this->gameHandler.processInput(this->glfwHandler.returnMainWindow(),
                                   deltaTime);
    // this->renderHandler.RenderBasic();
    this->gameHandler.update(deltaTime);
    this->glfwHandler.endLoop();
  }
}

void App::App::cleanup() {
  //
  this->glfwHandler.cleanupGlfwHandler();
  //
}
