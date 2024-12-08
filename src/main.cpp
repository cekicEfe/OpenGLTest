#include <exception>
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

#include "DemoGame/GameHandler/GameHandler.hpp"
#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/GlfwHandler/GlfwHandler.hpp>
#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>
#include <CoreClass/RenderHandler/RenderHandler.h>

#include <iostream>
#include <stdexcept>

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
          static GLfloat deltaTime;
          deltaTime = gameHandler.calculateDeltaTime ();

          gameHandler.update (deltaTime);
          glfwHandler.startOfLoop (deltaTime);

          ImGui::ShowDemoWindow ();

          {
            ImGui::Begin ("Close program");
            if (ImGui::Button ("Close"))
              {
                glfwHandler.terminateGlfw ();
                return 0;
              }
            ImGui::End ();
          }

          renderHandler.DrawInstanced (
              glfwHandler.returnMainWindow ().getScrWidth (),
              glfwHandler.returnMainWindow ().getScrHeight (),
              gameHandler.returnCamera (), gameHandler.returnLights (),
              gameHandler.returnLightsSize (), gameHandler.returnEntities (),
              gameHandler.returnEntitiesSize ());

          glfwHandler.endOfLoop ();
        }
    }
  catch (std::exception &e)
    {
      std::cout << "Error : " << e.what () << std::endl;
      std::cout << "Program closed unexpectedly" << std::endl;
      return -1;
    }
  std::cout << "Good bye" << std::endl;

  glfwHandler.terminateGlfw ();

  return 0;
}
