#include "InputHandler.hpp"
#include "glfw3.h"

core::InputHandler::InputHandler() {}
core::InputHandler::~InputHandler() {}

void core::InputHandler::setCursorCallbackFun(
    void (*cursorCallback)(GLFWwindow *, double, double)) {
  this->cursorCallback = cursorCallback;
}

void core::InputHandler::setFramebufferSizeCallbackFun(void (
    *framebufferSizeCallback)(GLFWwindow *window, int width, int height)) {
  this->framebufferSizeCallback = framebufferSizeCallback;
}

void core::InputHandler::setScrollCallback(void (*scrollCallback)(
    GLFWwindow *window, double xoffset, double yoffset)) {
  this->scrollCallback = scrollCallback;
}

void core::InputHandler::setInputMode(int inputMode, int inputValue) {
  this->inputMode = inputMode;
  this->inputValue = inputValue;
}

void core::InputHandler::setupCallbacks(GLFWwindow *window) {
  glfwSetInputMode(window, this->inputMode, this->inputValue);
  glfwSetCursorPosCallback(window, this->cursorCallback);
  glfwSetFramebufferSizeCallback(window, this->framebufferSizeCallback);
  glfwSetScrollCallback(window, this->scrollCallback);
}
