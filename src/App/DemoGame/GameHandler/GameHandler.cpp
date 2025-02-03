#include "GameHandler.hpp"
#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include "App/DemoGame/GameLight/GameLight.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "App/DemoGame/GameShader/GameShader.hpp"
#include "GraphicsBackend/Model/Model.h"
#include "glfw3.h"
#include <assimp/material.h>
#include <exception>
#include <filesystem>
#include <imgui.h>
#include <memory>

namespace fs = std::filesystem;

testgame::GameCamera testgame::GameHandler::mainCamera;
bool testgame::GameHandler::menuIsUp = true;

testgame::GameHandler::GameHandler() {}

testgame::GameHandler::~GameHandler() {}

void testgame::GameHandler::initDemo() {}

void testgame::GameHandler::demoMainLoop(const core::Window &window) {
  {
    static ImGui::FileBrowser browser;
    static std::string model = "Pick Model";
    static fs::path modelpath = "";
    {
      ImGui::Begin("Create Entity");

      ImGui::BulletText("Model : %s", model.c_str());
      ImGui::BulletText("Model path : %s", modelpath.c_str());

      if (ImGui::Button("Pick Model")) {
        browser.SetTitle("Pick Model");
        browser.SetTypeFilters({".obj"});
        browser.Open();
      }

      ImGui::End();
    }

    if (browser.HasSelected()) {
      modelpath = browser.GetSelected().string();
      model = modelpath.filename();
      browser.ClearSelected();
    }

    browser.Display();
  }
}

void testgame::GameHandler::demoCleanup() {}

void testgame::GameHandler::update(GLfloat deltaTime) {}

void testgame::GameHandler::mouse_callback(GLFWwindow *window, double xposIn,
                                           double yposIn) {
  if (!testgame::GameHandler::menuIsUp) {
    static double lastX = 0;
    static double lastY = 0;

    float ypos = static_cast<float>(yposIn);
    float xpos = static_cast<float>(xposIn);

    float xoffset = 0;
    float yoffset = 0;

    xoffset = xpos - lastX;
    yoffset = lastY - ypos; // reversed since y-coordinates go
                            // from bottom to top
    lastX = xpos;
    lastY = ypos;
    mainCamera.ProcessMouseMovement(xoffset, yoffset);
  }
};

void testgame::GameHandler::defaultFramebufferSizeCallback(GLFWwindow *window,
                                                           int width,
                                                           int height) {
  glViewport(0, 0, width, height);
};

void testgame::GameHandler::processInput(GLFWwindow *window,
                                         GLfloat deltaTime) {
  static int lasthitwaspress = 0;
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS && !lasthitwaspress) {
    if (testgame::GameHandler::menuIsUp) {
      testgame::GameHandler::menuIsUp = !testgame::GameHandler::menuIsUp;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
      testgame::GameHandler::menuIsUp = !testgame::GameHandler::menuIsUp;
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    lasthitwaspress = 1;
  }
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && lasthitwaspress) {
    lasthitwaspress = 0;
  }

  if (!testgame::GameHandler::menuIsUp) {

    static int shiftwaspressed = 0;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS &&
        !shiftwaspressed) {
      mainCamera.setSpeed(mainCamera.getSpeed() * 2);
      shiftwaspressed = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE &&
        shiftwaspressed) {
      shiftwaspressed = 0;
    }

    static int altwaspressed = 0;
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !altwaspressed) {
      mainCamera.setSpeed(mainCamera.getSpeed() / 2);
      altwaspressed = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE &&
        altwaspressed) {
      altwaspressed = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(DOWNWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      mainCamera.ProcessKeyboard(UPWARD, deltaTime);
  }
};

void testgame::GameHandler::scrollCallback(GLFWwindow *window, double xoffset,
                                           double yoffset) {
  if (!testgame::GameHandler::menuIsUp)
    mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
};

GLfloat testgame::GameHandler::calculateDeltaTime() {
  static GLfloat deltaTime = 0;
  static GLfloat lastFrame = 0;

  GLfloat currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;

  if (deltaTime >= 1.0f / 30.0f) {
    lastFrame = currentFrame;
  }

  return deltaTime;
}
