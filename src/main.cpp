#include <glad/glad.h>
//
//
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/GlfwHandler/GlfwHandler.hpp>
#include <CoreClass/OctTree/OctTree.hpp>
#include <CoreClass/RenderHandler/RenderHandler.h>

#include <iostream>

int
main (int argc, char **argv)
{
  core::GlfwHandler *glfwHandler = core::GlfwHandler::createInstance ();
  glfwHandler->initGlfw ("test", core::WINDOWED, 1000, 1000);

  while (!glfwHandler->checkWindowShouldClose ())
    {
      glfwHandler->startOfLoop (0);
      ImGui::ShowDemoWindow ();
      {
        ImGui::Begin ("Close program");
        if (ImGui::Button ("Close"))
          {
            // Here lies a warcrime
            goto END_PROGRAM;
          }
        ImGui::End ();
      }

      /*
        Do & Render here !!!
      */

      glfwHandler->endOfLoop ();
    }

END_PROGRAM:

  glfwHandler->terminateGlfw ();
  glfwHandler->deleteInstance ();

  std::cout << "Good bye" << std::endl;

  return 0;
}
