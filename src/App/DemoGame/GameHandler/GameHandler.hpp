#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "App/DemoGame/GameCamera/GameCamera.hpp"
#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include "App/DemoGame/GameEntity/HitBox/HitBox.h"
#include "App/DemoGame/GameLight/GameLight.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "App/DemoGame/GameShader/GameShader.hpp"
#include <vector>

namespace testgame {
class GameHandler {
private:
  static GameCamera mainCamera;

  std::vector<testgame::GameLight> lights;
  std::vector<testgame::GameModel> models;
  std::vector<testgame::GameShader> shaders;

  std::vector<HitBox> hitboxes;
  std::vector<testgame::GameEntity> entities;

public:
  GameHandler();
  ~GameHandler();

  void initDemo();

  const testgame::GameEntity *const returnEntities() const;
  const size_t returnEntitiesSize() const;

  const Model::Light *const returnLights() const;
  const size_t returnLightsSize() const;

  const GameCamera *const returnCamera() const;

  static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
  static void defaultFramebufferSizeCallback(GLFWwindow *window, int width,
                                             int height);
  void processInput(GLFWwindow *window, GLfloat deltaTime);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);

  GLfloat calculateDeltaTime();
  void update(GLfloat deltaTime);
};
} // namespace testgame

#endif
