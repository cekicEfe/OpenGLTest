#include "GameHandler.hpp"
#include "glfw3.h"
#include <exception>

namespace fs = std::filesystem;

testgame::GameCamera testgame::GameHandler::mainCamera;

testgame::GameHandler::GameHandler() {}

testgame::GameHandler::~GameHandler() {}

void testgame::GameHandler::initDemo() {
  try {
    auto find = [](const std::string &file) {
      fs::path path = fs::current_path();
      path = path.parent_path();

      if (fs::is_directory(path)) {
        for (const auto &entry : fs::directory_iterator(path)) {
          if (fs::is_directory(entry)) {
            for (const auto &nestedEntry :
                 fs::recursive_directory_iterator(entry.path())) {
              if (fs::is_regular_file(nestedEntry)) {
                if (nestedEntry.path().filename().string() == file) {
                  return nestedEntry.path().string();
                  break;
                }
              }
            }
          }
        }
      }
    };

    std::string jupiter_src("13905_Jupiter_V1_l3.obj");
    std::string backpack_src("backpack.obj");

    std::string vert("simpleVert.vert");
    std::string frag("simpleFrag.frag");
    std::string name("test");

    std::string jupiterModel;
    jupiterModel = find(jupiter_src);

    std::string backpackModel;
    backpackModel = find(backpack_src);

    std::string vertPath;
    vertPath = find(vert);

    std::string fragPath;
    fragPath = find(frag);

    this->models.emplace_back(jupiterModel, name, false);
    this->models.emplace_back(backpackModel, name, false);
    this->shaders.emplace_back(vertPath.c_str(), fragPath.c_str(), name);

    this->lights.push_back(testgame::GameLight());
    this->lights[0].light_pos = {0.0f, 15.0f, 0.0f};
    this->lights[0].light_color = {0.7f, 0.7f, 0.7f};

    this->entities.push_back(testgame::GameEntity());
    this->entities[0].setPos({500.0f, 0.0f, 0.0f});
    this->entities[0].setModel(&this->models[0]);
    this->entities[0].setShader(&this->shaders[0]);

    this->entities.push_back(testgame::GameEntity());
    this->entities[1].setPos({-500.0f, 0.0f, 0.0f});
    this->entities[1].setModel(&this->models[0]);
    this->entities[1].setShader(&this->shaders[0]);

    this->entities.push_back(testgame::GameEntity());
    this->entities[2].setPos({0.0f, 0.0f, 0.0f});
    this->entities[2].setModel(&this->models[1]);
    this->entities[2].setShader(&this->shaders[0]);
  } catch (std::exception &e) {
    std::cout << "Error occured at GameHandler::initDemo" << e.what()
              << std::endl;
  }
}

const testgame::GameEntity *const
testgame::GameHandler::returnEntities() const {
  return this->entities.data();
}

const size_t testgame::GameHandler::returnEntitiesSize() const {
  return this->entities.size();
}

const Model::Light *const testgame::GameHandler::returnLights() const {
  return this->lights.data();
}

const size_t testgame::GameHandler::returnLightsSize() const {
  return this->lights.size();
}

const testgame::GameCamera *const testgame::GameHandler::returnCamera() const {
  return &this->mainCamera;
}

void testgame::GameHandler::update(GLfloat deltaTime) {}

void testgame::GameHandler::mouse_callback(GLFWwindow *window, double xposIn,
                                           double yposIn) {
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
  if (!mainCamera.getStatus())
    mainCamera.ProcessMouseMovement(xoffset, yoffset);
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
    if (mainCamera.getStatus() == true) {
      mainCamera.setStatus(!mainCamera.getStatus());
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    } else {
      mainCamera.setStatus(!mainCamera.getStatus());
      glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    lasthitwaspress = 1;
  }
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_RELEASE && lasthitwaspress) {
    lasthitwaspress = 0;
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    mainCamera.setSpeed(SPEED * 2);
  else
    mainCamera.setSpeed(SPEED);

  if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    mainCamera.setSpeed(SPEED / 2);
  else
    mainCamera.setSpeed(SPEED);

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
};

void testgame::GameHandler::scrollCallback(GLFWwindow *window, double xoffset,
                                           double yoffset) {
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
