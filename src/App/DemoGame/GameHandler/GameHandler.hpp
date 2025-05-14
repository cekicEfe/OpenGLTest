#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "App/DemoGame/GameCamera/GameCamera.hpp"
#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include "App/DemoGame/GameHitBox/GameHitBox.hpp"
#include "App/DemoGame/GameLight/GameLight.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "App/DemoGame/GameShader/GameShader.hpp"
#include "CoreBackend/GlfwHandler/WindowHandler/Window/Window.h"
#include "imgui.h"
#include "imguiFileExplorer/imfilebrowser.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace testgame
{

class GameHandler
{
private:
  std::vector<std::shared_ptr<GameHitBox> > hitboxes;
  std::vector<std::shared_ptr<GameLight> > lights;
  std::vector<std::shared_ptr<GameModel> > models;
  std::vector<std::shared_ptr<GameShader> > shaders;
  std::vector<std::shared_ptr<GameEntity> > entities;

  static GameCamera mainCamera;
  static bool menuIsUp;

  void demoShowGui ();
  GLfloat calculateDeltaTime ();
  void update (GLfloat deltaTime);
  void processInput (GLFWwindow *window, GLfloat deltaTime);

public:
  GameHandler ();
  ~GameHandler ();

  void demoInit ();
  void demoMainLoop (const core::Window &window);
  void demoCleanup ();

  static void mouse_callback (GLFWwindow *window, double xposIn,
                              double yposIn);
  static void defaultFramebufferSizeCallback (GLFWwindow *window, int width,
                                              int height);
  static void scrollCallback (GLFWwindow *window, double xoffset,
                              double yoffset);
};

} // namespace testgame

#endif
