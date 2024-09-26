#include "MainHandler.h"
#include <memory>
#include <vector>

std::unordered_map<std::string,
                   std::pair<std::unique_ptr<Model::Model>,
                             std::vector<std::shared_ptr<core::CoreEntity>>>>
    core::MainHandler::msEntityBatch;

std::vector<std::string> core::MainHandler::msJsonScenePaths;
std::vector<std::string> core::MainHandler::msJsonPreceptPaths;
std::vector<std::string> core::MainHandler::msShaderPaths;

std::vector<std::unique_ptr<Model::Light>> core::MainHandler::msLights;
std::vector<std::unique_ptr<Shader>> core::MainHandler::msShaders;

std::vector<std::unique_ptr<nlohmann::json>> core::MainHandler::msJsonScenes;
std::vector<std::unique_ptr<nlohmann::json>> core::MainHandler::msJsonPrecepts;

// Gui related functions
void core::MainHandler::showGui() {}

// Runtime related functions
void core::MainHandler::addCoreEntity() {}

void core::MainHandler::addCoreEntity(Model::Model *entityModel) {}

// System related functions
void core::MainHandler::processInput(GLFWwindow *window, GLfloat deltaTime)
{
  // wait time for pressing esc
  static GLfloat waitTime = 0.0f;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && waitTime <= 0)
  {
    MainHandlerVariables.simuFlag = !MainHandlerVariables.simuFlag;
    MainHandlerVariables.firstMouse = true;
    glfwSetCursorPos(window, MainHandlerVariables.SCR_WIDTH / 2,
                     MainHandlerVariables.SCR_HEIGHT / 2);
    waitTime = 0.35f;
  }
  if (MainHandlerVariables.simuFlag)
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.MovementSpeed = SPEED * 2;
    else
      MainHandlerVariables.mainCamera.MovementSpeed = SPEED;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.MovementSpeed = SPEED / 2;
    else
      MainHandlerVariables.mainCamera.MovementSpeed = SPEED;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          FORWARD, MainHandlerVariables.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          BACKWARD, MainHandlerVariables.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          LEFT, MainHandlerVariables.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          RIGHT, MainHandlerVariables.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          DOWNWARD, MainHandlerVariables.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      MainHandlerVariables.mainCamera.ProcessKeyboard(
          UPWARD, MainHandlerVariables.deltaTime);
  }
  else
  {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
  // decreases wait time
  if (waitTime - deltaTime <= 0) // somehow
    waitTime = 0;
  else
    waitTime -= deltaTime;
}

void core::MainHandler::DrawInstanced()
{
  core::RenderHandler::DrawInstanced(core::MainHandlerVariables.SCR_WIDTH,
                                     core::MainHandlerVariables.SCR_HEIGHT,
                                     &core::MainHandlerVariables.mainCamera,
                                     &core::MainHandler::msShaders,
                                     &core::MainHandler::msLights,
                                     &core::MainHandler::msEntityBatch);
}

void core::MainHandler::DrawInstancedWithInterval(GLfloat deltaTime,
                                                  GLfloat intervalMS) {}

void core::MainHandler::framebuffer_size_callback(GLFWwindow *window, int width,
                                                  int height)
{
  glViewport(0, 0, width, height);
}

void core::MainHandler::mouse_callback(GLFWwindow *window, double xposIn,
                                       double yposIn)
{
  float ypos = static_cast<float>(yposIn);
  float xpos = static_cast<float>(xposIn);

  float xoffset = 0;
  float yoffset = 0;

  if (MainHandlerVariables.simuFlag)
  {
    if (MainHandlerVariables.firstMouse)
    {
      MainHandlerVariables.lastX = xpos;
      MainHandlerVariables.lastY = ypos;
      MainHandlerVariables.firstMouse = false;
    }
    else
    {
      xoffset = xpos - MainHandlerVariables.lastX;
      yoffset = MainHandlerVariables.lastY -
                ypos; // reversed since y-coordinates go from bottom to top

      MainHandlerVariables.lastX = xpos;
      MainHandlerVariables.lastY = ypos;
    }

    MainHandlerVariables.mainCamera.ProcessMouseMovement(xoffset, yoffset);
  }
}

void core::MainHandler::scroll_callback(GLFWwindow *window, double xoffset,
                                        double yoffset)
{
  if (MainHandlerVariables.simuFlag)
    MainHandlerVariables.mainCamera.ProcessMouseScroll(
        static_cast<float>(yoffset));
}

void core::MainHandler::calculateDeltaTime()
{
  float currentFrame = static_cast<float>(glfwGetTime());
  MainHandlerVariables.deltaTime =
      currentFrame - MainHandlerVariables.lastFrame;
  MainHandlerVariables.counter++;

  if (MainHandlerVariables.deltaTime >= 1.0f / 30.0f)
  {
    MainHandlerVariables.lastFrame = currentFrame;
    MainHandlerVariables.counter = 0;
  }
}

GLfloat core::MainHandler::returnDeltaTime()
{
  return MainHandlerVariables.deltaTime;
}

GLuint core::MainHandler::returnSCR_WIDTH()
{
  return core::MainHandlerVariables.SCR_WIDTH;
}

GLuint core::MainHandler::returnSCR_HEIGHT()
{
  return core::MainHandlerVariables.SCR_HEIGHT;
}
