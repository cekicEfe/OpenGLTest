#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "CoreClass/CoreEntity/CoreEntity.h"
#include "DemoGame/GameCamera/GameCamera.hpp"
#include "DemoGame/GameEntity/GameEntity.hpp"
#include "DemoGame/GameEntity/HitBox/HitBox.h"
#include "model/Camera.h"
#include "model/Model.h"
#include "model/Shaders.h"
#include <vector>

namespace testgame
{
class GameHandler
{
private:
  GameHandler (GameHandler &other) = delete;
  void operator= (const GameHandler &) = delete;

  static GameCamera mainCamera;

  std::vector<Shader> shaders;
  std::vector<Model::Light> lights;
  std::vector<Model::Model> models;

  std::vector<HitBox> hitboxes;
  std::vector<testgame::GameEntity> entities;

public:
  GameHandler ();
  ~GameHandler ();

  const testgame::GameEntity *const returnEntities () const;
  const size_t returnEntitiesSize () const;

  const std::vector<Model::Light> &returnLights () const;
  Camera const &returnCamera () const;

  static void mouse_callback (GLFWwindow *window, double xposIn,
                              double yposIn);

  static void defaultFramebufferSizeCallback (GLFWwindow *window, int width,
                                              int height);

  static void processInput (GLFWwindow *window, GLfloat deltaTime);

  static void scrollCallback (GLFWwindow *window, double xoffset,
                              double yoffset);
};
}

#endif
