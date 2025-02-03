#include "App/App.hpp"
//
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <CoreBackend/GlfwHandler/GlfwHandler.hpp>
#include <CoreBackend/RenderHandler/RenderHandler.h>

#include <iostream>

using namespace core;

int
main (int argc, char **argv)
{
  // freopen ("log.txt", "w", stdout);
  // std::cout << "Starting program" << std::endl;

  App::App app;

  try
    {
      app.init ();
    }
  catch (std::exception &e)
    {
      std::cout << "This exception occured at app.init()... : " << e.what ()
                << std::endl;
      return -1;
    }

  try
    {
      app.mainLoop ();
    }
  catch (std::exception &e)
    {
      std::cout << "This exception occured at app.mainLoop()... : "
                << e.what () << std::endl;
      return -1;
    }

  try
    {
      app.cleanup ();
    }
  catch (std::exception &e)
    {
      std::cout << "This exception occured at app.mainLoop()... : "
                << e.what () << std::endl;
      return -1;
    }

  std::cout << "Good bye" << std::endl;
  return 0;
}
