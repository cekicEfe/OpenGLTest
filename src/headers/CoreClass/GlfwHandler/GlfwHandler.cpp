#include "GlfwHandler.hpp"
#include "glfw3.h"

core::GlfwHandler::GlfwHandler ()
{
}

core::GlfwHandler::~GlfwHandler ()
{
}

void
core::GlfwHandler::initGlfw (
    std::string windowName, WindowType type, GLuint SCR_WIDTH,
    GLuint SCR_HEIGHT, int inputMode, int inputValue,
    void (*frameSizeCallback) (GLFWwindow *window, int width, int height),
    void (*mouseCallback) (GLFWwindow *window, double xposIn, double yposIn),
    void (*scrollCallback) (GLFWwindow *window, double xoffset,
                            double yoffset),
    void (*inputProcessor) (GLFWwindow *window, GLfloat deltaTime))
{
  static GLuint initCallCount = 1;

  if (initCallCount >= 1)
    {
      std::cout << "Initializing glfw" << std::endl;
      if (!glfwInit ())
        {
          std::cerr << "GLFW initialization failed!" << std::endl;
          auto out = core::ErrorHandler::ReturnOpenglError ();
          throw -1;
        }

      glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
      glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      // For antialising
      // glfwWindowHint(GLFW_SAMPLES, 4);

      this->windowHandler.createMainWindow (windowName, type, SCR_WIDTH,
                                            SCR_HEIGHT);

      glfwMakeContextCurrent (this->windowHandler.returnMainGLFWWindow ());

      // static auto defaultFramebufferSizeCallback
      //     = [] (GLFWwindow *, int width, int height) {
      //         glViewport (0, 0, width, height);
      //       };
      this->setMainWindowInputMode (inputMode, inputValue);
      this->setMainWindowFramebufferSizeCallback (frameSizeCallback);
      this->setMainWindowMouseCallback (mouseCallback);
      this->setMainWindowScrollCallback (scrollCallback);
      this->setMainWindowInputProcessor (inputProcessor);

      std::cout << "Initializing GLAD" << std::endl;
      if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
        {
          std::cout << "Failed to initialize GLAD" << std::endl;
          throw -1;
        }

      std::cout << "Enabling optimizing and antialising" << std::endl;

      // For optimizing
      glEnable (GL_DEPTH_TEST);
      glEnable (GL_CULL_FACE);
      // For antialising
      // glEnable (GL_MULTISAMPLE);
      this->imguiHandler.initImGui (
          this->windowHandler.returnMainGLFWWindow ());
    }
  else
    {
      std::cout << "Glfw is already initliazed" << std::endl;
    }
}

void
core::GlfwHandler::terminateGlfw ()
{
  std::cout << "Terminating glfw" << std::endl;
  this->imguiHandler.terminateImgui ();
  glfwTerminate ();
}

void
core::GlfwHandler::processInput (GLfloat deltaTime)
{
  if (this->inputProcessor != nullptr)
    (*this->inputProcessor) (this->windowHandler.returnMainGLFWWindow (),
                             deltaTime);
}

void
core::GlfwHandler::startOfLoop (GLfloat deltaTime)
{
  this->processInput (deltaTime);
  this->setLoopVariables ();
}

void
core::GlfwHandler::endOfLoop ()
{
  this->swapBuffers ();
  this->pollEvents ();
}

GLuint
core::GlfwHandler::checkWindowShouldClose ()
{
  return glfwWindowShouldClose (this->windowHandler.returnMainGLFWWindow ());
}

const core::Window &
core::GlfwHandler::returnMainWindow () const
{
  return this->windowHandler.returnMainWindow ();
}

void
core::GlfwHandler::setLoopVariables ()
{
  glClearColor (0.20f, 0.20f, 0.20f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace (GL_BACK);

  this->imguiHandler.initLoop ();
}

void
core::GlfwHandler::swapBuffers ()
{
  this->imguiHandler.render ();
  glfwSwapBuffers (this->windowHandler.returnMainGLFWWindow ());
}

void
core::GlfwHandler::pollEvents ()
{
  glfwPollEvents ();
}

void
core::GlfwHandler::setMainWindowMouseCallback (
    void (*func) (GLFWwindow *window, double xposIn, double yposIn))
{
  glfwSetCursorPosCallback (this->windowHandler.returnMainGLFWWindow (),
                            (GLFWcursorposfun)func);
}

void
core::GlfwHandler::setMainWindowFramebufferSizeCallback (

    void (*func) (GLFWwindow *window, int width, int height))
{
  glfwSetFramebufferSizeCallback (this->windowHandler.returnMainGLFWWindow (),
                                  (GLFWframebuffersizefun)func);
}

void
core::GlfwHandler::setMainWindowScrollCallback (
    void (*func) (GLFWwindow *window, double xoffset, double yoffset))
{
  glfwSetScrollCallback (this->windowHandler.returnMainGLFWWindow (),
                         (GLFWscrollfun)func);
}

void
core::GlfwHandler::setMainWindowInputMode (int mode, int value)
{
  glfwSetInputMode (this->windowHandler.returnMainGLFWWindow (), mode, value);
}

void
core::GlfwHandler::setMainWindowInputProcessor (
    void (*func) (GLFWwindow *window, GLfloat deltaTime))
{
  this->inputProcessor = func;
}
