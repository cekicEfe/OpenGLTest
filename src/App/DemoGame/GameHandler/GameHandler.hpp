#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "App/DemoGame/GameCamera/GameCamera.hpp"
#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include "App/DemoGame/GameEntity/HitBox/HitBox.h"
#include "App/DemoGame/GameLight/GameLight.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "App/DemoGame/GameShader/GameShader.hpp"
#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include "imgui.h"
#include "imguiFileExplorer/imfilebrowser.h"
#include <vector>

namespace testgame {
class GameHandler {
private:
  std::vector<std::unique_ptr<HitBox>> hitboxes;
  std::vector<std::unique_ptr<testgame::GameLight>> lights;
  std::vector<std::unique_ptr<testgame::GameModel>> models;
  std::vector<std::unique_ptr<testgame::GameShader>> shaders;
  std::vector<std::unique_ptr<testgame::GameEntity>> entities;

  static GameCamera mainCamera;
  static bool menuIsUp;

public:
  GameHandler();
  ~GameHandler();

  void initDemo();
  void demoMainLoop(const core::Window &window);
  void demoCleanup();

  GLfloat calculateDeltaTime();
  void update(GLfloat deltaTime);
  void processInput(GLFWwindow *window, GLfloat deltaTime);

  static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
  static void defaultFramebufferSizeCallback(GLFWwindow *window, int width,
                                             int height);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
};
} // namespace testgame

#endif
