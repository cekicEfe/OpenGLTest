#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>

core::Window::Window ()
{
  this->window = nullptr;
  this->windowIsSet = 0;
}

core::Window::Window (std::string windowName, WindowType type,
                      GLuint SCR_WIDTH, GLuint SCR_HEIGHT)
    : windowName (windowName), type (type), SCR_WIDTH (SCR_WIDTH),
      SCR_HEIGHT (SCR_HEIGHT)
{
  this->window = nullptr;
  this->windowIsSet = 0;
}

core::Window::~Window ()
{
  if (this->window != nullptr)
    {
      glfwDestroyWindow (this->window);
      this->window = nullptr;
      this->windowIsSet = 0;
    }
  else
    {
      this->window = nullptr;
      this->windowIsSet = 0;
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

void
core::Window::createWindow ()
{
  if (windowIsSet == 0)
    {
      std::cout << "Creating window" << std::endl;
      switch (this->type)
        {
        case FULL_SCREEN:
          this->window = glfwCreateWindow (this->SCR_WIDTH, this->SCR_HEIGHT,
                                           windowName.c_str (),
                                           glfwGetPrimaryMonitor (), NULL);
          // checks if windows is created succesfully
          if (this->window == NULL)
            {
              std::cout << "Failed to create GLFW window" << std::endl;
              auto out = core::ErrorHandler::ReturnOpenglError ();
              throw -1;
            }
          break;
        case WINDOWED:
          this->window = glfwCreateWindow (this->SCR_WIDTH, this->SCR_HEIGHT,
                                           windowName.c_str (), NULL, NULL);
          // checks if windows is created succesfully
          if (this->window == NULL)
            {
              std::cout << "Failed to create GLFW window" << std::endl;
              auto out = core::ErrorHandler::ReturnOpenglError ();
              throw -1;
            }
          break;
        default:
          throw std::invalid_argument ("No proper window type was given");
          break;
        }
      this->windowIsSet = 1;
    }
  else
    {
      std::cout << "Window is already active" << std::endl;
    }
}

void
core::Window::destroyWindow ()
{
  if (this->window != nullptr)
    {
      glfwDestroyWindow (this->window);
      this->window = nullptr;
      this->windowIsSet = 0;
    }
  else
    {
      this->window = nullptr;
      this->windowIsSet = 0;
    }
}

GLFWwindow *
core::Window::returnGLFWWindow ()
{
  return this->window;
}
