#include <CoreClass/GlfwHandler/WindowHandler/Window/Window.h>
#include <glad/glad.h>
#include <glm/fwd.hpp>
//
//
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

#include <CoreClass/ErrorHandler/ErrorHandler.hpp>
#include <CoreClass/GlfwHandler/GlfwHandler.hpp>
#include <CoreClass/RenderHandler/RenderHandler.h>

#include <iostream>

static Camera camera;
static int callC = 0;

int
main (int argc, char **argv)
{
  core::GlfwHandler *glfwHandler = core::GlfwHandler::createInstance ();

  const core::RenderHandler *renderHandler
      = core::RenderHandler::createInstance ();

  static char lastKey = ' ';
  static double lastX = 0;
  static double lastY = 0;
  static bool cameraIsHalted = false;

  static auto mouse_callback
      = [] (GLFWwindow *window, double xposIn, double yposIn) {
          float ypos = static_cast<float> (yposIn);
          float xpos = static_cast<float> (xposIn);

          float xoffset = 0;
          float yoffset = 0;

          xoffset = xpos - lastX;
          yoffset = lastY - ypos; // reversed since y-coordinates go
                                  // from bottom to top
          lastX = xpos;
          lastY = ypos;
          if (!cameraIsHalted)
            camera.ProcessMouseMovement (xoffset, yoffset);
        };

  static auto defaultFramebufferSizeCallback
      = [] (GLFWwindow *, int width, int height) {
          glViewport (0, 0, width, height);
        };

  auto static processInput = [] (GLFWwindow *window, GLfloat deltaTime) {
    if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      {
        if (cameraIsHalted)
          {
            cameraIsHalted = !cameraIsHalted;
            glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
          }
        else
          {
            cameraIsHalted = !cameraIsHalted;
            glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
          }
      }
    if (glfwGetKey (window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      camera.MovementSpeed = SPEED * 2;
    else
      camera.MovementSpeed = SPEED;
    if (glfwGetKey (window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
      camera.MovementSpeed = SPEED / 2;
    else
      camera.MovementSpeed = SPEED;
    if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS)
      camera.ProcessKeyboard (FORWARD, deltaTime), lastKey = 'w';
    if (glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS)
      camera.ProcessKeyboard (BACKWARD, deltaTime), lastKey = 's';
    if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS)
      camera.ProcessKeyboard (LEFT, deltaTime), lastKey = 'a';
    if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS)
      camera.ProcessKeyboard (RIGHT, deltaTime), lastKey = 'd';
    if (glfwGetKey (window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
      camera.ProcessKeyboard (DOWNWARD, deltaTime), lastKey = 'c';
    if (glfwGetKey (window, GLFW_KEY_SPACE) == GLFW_PRESS)
      camera.ProcessKeyboard (UPWARD, deltaTime), lastKey = ' ';
  };

  static auto scrollCallback
      = [] (GLFWwindow *window, double xoffset, double yoffset) {
          camera.ProcessMouseScroll (static_cast<float> (yoffset));
        };

  glfwHandler->initGlfw ("test", core::WINDOWED, 1920, 1080,
                         defaultFramebufferSizeCallback, mouse_callback,
                         scrollCallback, processInput, GLFW_CURSOR,
                         GLFW_CURSOR_NORMAL);
  // Demo
  Model::Model backPack ("../models/backpack_model/backpack.obj");
  Shader shader ("../shaders/simpleVert.vert", "../shaders/simpleFrag.frag");
  std::vector<Model::Light> lights;
  Model::Light light;
  light.light_pos = { 0.0, 15.0, 0.0 };
  light.light_color = { 0.5, 0.5, 0.5 };

  lights.push_back (light);
  light.light_pos = { -5.0, 10.0, 0.0 };
  light.light_color = { 0.5, 0.5, 0.5 };

  lights.push_back (light);

  std::vector<std::unique_ptr<core::CoreEntity> > entities;
  entities.push_back (std::make_unique<core::CoreEntity> ());
  entities.push_back (std::make_unique<core::CoreEntity> ());

  entities.at (0).get ()->setModel (&backPack);
  entities.at (0).get ()->setShader (&shader);
  entities.at (0)->setPos ({ 11.0f, 5.0f, 3.0f });
  entities.at (1).get ()->setModel (&backPack);
  entities.at (1).get ()->setShader (&shader);

  camera.Position = glm::vec3 (-5.0f, 0.0f, 0.0f);
  // !Demo

  while (!glfwHandler->checkWindowShouldClose ())
    {
      glfwHandler->startOfLoop (0.1);
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

      {
        ImGui::Begin ("Camera things");
        ImGui::Text ("Camera dir : %f %f %f", camera.Yaw, camera.Front.y,
                     camera.Front.z);
        ImGui::Text ("Last x : %f last y : %f", lastX, lastY);

        ImGui::Text ("Call count %d", callC);
        ImGui::End ();
      }

      /*
        Do & Render here !!!
      */
      renderHandler->DrawInstanced (
          glfwHandler->returnMainWindow ().getScrWidth (),
          glfwHandler->returnMainWindow ().getScrHeight (), &camera, &lights,
          &entities);

      glfwHandler->endOfLoop ();
    }

END_PROGRAM:

  glfwHandler->terminateGlfw ();
  glfwHandler->deleteInstance ();
  renderHandler->deleteInstance ();

  std::cout << "Good bye" << std::endl;

  return 0;
}
