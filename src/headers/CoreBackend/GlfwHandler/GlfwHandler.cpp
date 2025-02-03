#include "GlfwHandler.hpp"
#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include <imgui.h>

core::GlfwHandler::GlfwHandler ()
{
}

core::GlfwHandler::~GlfwHandler ()
{
}

void
core::GlfwHandler::initGlfwHandler (std::string windowName, GLuint SCR_WIDTH,
                                    GLuint SCR_HEIGHT)
{

  std::cout << "Initializing glfw at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  if (!glfwInit ())
    {
      std::cerr << "GLFW initialization failed at "
                   "core::GlfwHandler::initGlfwHandler!"
                << std::endl;
      auto out = core::ErrorHandler::ReturnGLFWError ();
      throw -1;
    }

  std::cout << "Hinting glfw window at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // For antialising
  // glfwWindowHint(GLFW_SAMPLES, 4);

  std::cout << "Creating window at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  this->windowHandler.createMainWindow (windowName, core::WINDOWED, SCR_WIDTH,
                                        SCR_HEIGHT);

  std::cout
      << "Making window current context at core::GlfwHandler::initGlfwHandler"
      << std::endl;
  glfwMakeContextCurrent (this->windowHandler.returnMainGLFWWindow ());

  std::cout << "Setting up callbacks at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  this->inputHandler.setupCallbacks (
      this->windowHandler.returnMainGLFWWindow ());

  std::cout << "Initializing GLAD at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  if (!gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress))
    {
      std::cout << "Failed to initialize GLAD" << std::endl;
      throw -1;
    }

  std::cout << "Enabling optimizing at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  // For optimizing
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  // For antialising
  // glEnable (GL_MULTISAMPLE);

  std::cout << "Initilizing ImGui at core::GlfwHandler::initGlfwHandler"
            << std::endl;
  this->initImGui ();
}

GLuint
core::GlfwHandler::checkWindowShouldClose ()
{
  return glfwWindowShouldClose (this->windowHandler.returnMainGLFWWindow ());
}

void
core::GlfwHandler::beginLoop ()
{
  this->setLoopVariables ();
  this->initLoopImGui ();
  ImGui::ShowDemoWindow ();
}

const core::Window &
core::GlfwHandler::returnMainWindow ()
{
  return this->windowHandler.returnMainWindow ();
}

void
core::GlfwHandler::endLoop ()
{
  this->renderImGui ();
  this->swapBuffers ();
  this->pollEvents ();
}

void
core::GlfwHandler::cleanupGlfwHandler ()
{
  std::cout << "Terminating glfw at core::GlfwHandler::cleanupGlfwHandler()"
            << std::endl;
  this->imguiHandler.terminateImgui ();
  this->windowHandler.destroyMainWindow ();
  glfwTerminate ();
  std::cout << "Terminated glfw" << std::endl;
}

void
core::GlfwHandler::setLoopVariables ()
{
  glClearColor (1.0f, 1.0f, 1.0f, 1.0f);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCullFace (GL_BACK);
}

void
core::GlfwHandler::swapBuffers ()
{
  glfwSwapBuffers (this->windowHandler.returnMainGLFWWindow ());
}

void
core::GlfwHandler::pollEvents ()
{
  glfwPollEvents ();
}

void
core::GlfwHandler::initImGui ()
{
  std::cout << "Initilizing ImGui at core::GlfwHandler::initImGui()"
            << std::endl;
  this->imguiHandler.initImGui (this->windowHandler.returnMainGLFWWindow ());
}

void
core::GlfwHandler::initLoopImGui ()
{
  this->imguiHandler.initLoop ();
}

void
core::GlfwHandler::renderImGui ()
{
  this->imguiHandler.render ();
}

void
core::GlfwHandler::terminateImGui ()
{
  std::cout << "Terminating Imgui at core::GlfwHandler::terminateImGui()"
            << std::endl;
  this->imguiHandler.terminateImgui ();
}
