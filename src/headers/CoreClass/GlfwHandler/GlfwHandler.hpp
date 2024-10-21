#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <model/Camera.h>
//
#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

namespace core {

class GlfwHandler {
private:
  static GLuint SCR_WIDTH;
  static GLuint SCR_HEIGHT;
  static GLfloat lastX;
  static GLfloat lastY;
  static GLboolean firstMouse;
  static GLuint counter;
  static GLboolean simuFlag;
  static GLfloat deltaTime;
  static GLfloat lastFrame;

  static Camera mainCamera;

  static core::GlfwHandler *instance;
  static GLFWwindow *window;

  GlfwHandler();
  ~GlfwHandler();

  // Input related functions to make glfw point at YOUR functions
  static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow *window, double xoffset,
                              double yoffset);
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);

public:
  // Use to create instance
  static core::GlfwHandler *createInstance();
  // Use to delete instance
  void deleteInstance();

  // Use to set up glfw
  void setLoopVariables();
  void swapBuffers();
  void initGlfw();
  void terminateGlfw();

  // For main loop checks if main window is closed
  GLboolean checkWindowShouldClose();
  GLFWwindow *returnWindow();

  // Input related use it at main loop
  void calculateDeltaTime();
  GLfloat returnDeltaTime();
  void processInput(GLFWwindow *window, GLfloat deltaTime);
};

} // namespace core

#endif
