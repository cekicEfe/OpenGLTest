#include <cstdlib>
#include <glad/glad.h>
//
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "CoreClass/CoreEntity/CoreEntity.h"
#include "DemoGame/GameEntity/GameEntity.hpp"
#include "DemoGame/GameHandler/GameHandler.hpp"
#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/GlfwHandler/GlfwHandler.hpp>
#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>
#include <CoreClass/RenderHandler/RenderHandler.h>

#include <iostream>

using namespace testgame;
using namespace core;

int
main (int argc, char **argv)
{
  GameHandler gameHandler;
  GlfwHandler glfwHandler;
  RenderHandler renderHandler;

  glfwHandler.initGlfw (
      "test", core::WINDOWED, 1920, 1080, GLFW_CURSOR, GLFW_CURSOR_NORMAL,
      gameHandler.defaultFramebufferSizeCallback, gameHandler.mouse_callback,
      gameHandler.scrollCallback, gameHandler.processInput);

  try
    {
      while (!glfwHandler.checkWindowShouldClose ())
        {
          glfwHandler.startOfLoop (0.1);
          ImGui::ShowDemoWindow ();

          {
            ImGui::Begin ("Close program");
            if (ImGui::Button ("Close"))
              {
                exit (EXIT_SUCCESS);
              }
            ImGui::End ();
          }

          {
            ImGui::Begin ("Camera things");

            ImGui::End ();
          }

          /*
            Do & Render here !!!
          */
          //         renderHandler->DrawInstanced (
          //             glfwHandler->returnMainWindow ().getScrWidth (),
          //             glfwHandler->returnMainWindow ().getScrHeight (),
          //             &cameraTest, &lights, entities.data (), entities.size
          //             ());

          glfwHandler.endOfLoop ();
        }
    }
  catch (...)
    {
      std::cout << "Program closed unexpectedly" << std::endl;
      std::cout << "Bad bye" << std::endl;
      return -1;
    }
  std::cout << "Good bye" << std::endl;

  return 0;
}
