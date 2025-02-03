#include <CoreBackend/ErrorHandler/ErrorHandler.hpp>
#include <CoreBackend/GlfwHandler/WindowHandler/Window/Window.h>
#include <stdexcept>

core::Window::Window (std::string windowName, WindowType type,
                      GLuint SCR_WIDTH, GLuint SCR_HEIGHT)
    : windowName (windowName), type (type), SCR_WIDTH (SCR_WIDTH),
      SCR_HEIGHT (SCR_HEIGHT)
{
  this->createWindow ();
}

core::Window::~Window ()
{
  this->destroyWindow ();
}

void
core::Window::createWindow ()
{
  if (windowIsSet == 0)
    {
      std::cout << "Creating window at core::Window::createWindow()"
                << std::endl;
      switch (this->type)
        {
        case FULL_SCREEN:
          this->window = glfwCreateWindow (this->SCR_WIDTH, this->SCR_HEIGHT,
                                           windowName.c_str (),
                                           glfwGetPrimaryMonitor (), NULL);
          // checks if windows is created succesfully
          if (this->window == NULL)
            {
              std::cout << "Failed to create GLFW window at "
                           "core::Window::createWindow()"
                        << std::endl;
              auto out = core::ErrorHandler::ReturnGLFWError ();
              throw -1;
            }
          break;
        case WINDOWED:
          this->window = glfwCreateWindow (this->SCR_WIDTH, this->SCR_HEIGHT,
                                           windowName.c_str (), NULL, NULL);
          // checks if windows is created succesfully
          if (this->window == NULL)
            {
              std::cout << "Failed to create GLFW window  at "
                           "core::Window::createWindow()"
                        << std::endl;
              auto out = core::ErrorHandler::ReturnGLFWError ();
              throw -1;
            }
          break;
        default:
          throw std::invalid_argument ("No proper window type was given at "
                                       "core::Window::createWindow()");
          break;
        }
      this->windowIsSet = 1;
    }
  else
    {
      throw std::runtime_error (
          "This window is already created at core::Window::createWindow()");
    }
}

void
core::Window::destroyWindow ()
{
  if (this->window != nullptr)
    {
      std::cout << "Window :" << this->window
                << "is destoyed at core::Window::destroyWindow()" << std::endl;
      glfwDestroyWindow (this->window);
      this->window = nullptr;
      this->windowIsSet = 0;
    }
  else if (this->window == nullptr)
    {
      throw std::runtime_error ("A window is tried to be destroyed again "
                                "core::Window::destroyWindow()");
    }
}

const GLuint &
core::Window::getScrWidth () const
{
  return this->SCR_WIDTH;
};

const GLuint &
core::Window::getScrHeight () const
{
  return this->SCR_WIDTH;
};

GLFWwindow *
core::Window::returnGLFWWindow () const
{
  return this->window;
}
