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
#include <vector>

#define SOL_ALL_SAFETIES_ON 1
extern "C" {
#include <lua.h>
#include <lualib.h>
}

#include <sol/sol.hpp>

#ifndef EXAMPLES_ASSERT_HPP
#define EXAMPLES_ASSERT_HPP
#define m_assert(condition, message)                                           \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__         \
                << " line " << __LINE__ << ": " << message << std::endl;       \
      std::terminate();                                                        \
    }                                                                          \
  } while (false)

#define c_assert(condition)                                                    \
  do {                                                                         \
    if (!(condition)) {                                                        \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__         \
                << " line " << __LINE__ << std::endl;                          \
      std::terminate();                                                        \
    }                                                                          \
  } while (false)
#else
#define m_assert(condition, message)                                           \
  do {                                                                         \
    if (false) {                                                               \
      (void)(condition);                                                       \
      (void)sizeof(message);                                                   \
    }                                                                          \
  } while (false)
#define c_assert(condition)                                                    \
  do {                                                                         \
    if (false) {                                                               \
      (void)(condition);                                                       \
    }                                                                          \
  } while (false)
#endif

namespace testgame {

class GameHandler {
private:
  std::vector<std::shared_ptr<GameHitBox>> hitboxes;
  std::vector<std::shared_ptr<GameLight>> lights;
  std::vector<std::shared_ptr<GameModel>> models;
  std::vector<std::shared_ptr<GameShader>> shaders;
  std::vector<std::shared_ptr<GameEntity>> entities;
  std::unique_ptr<sol::state> scriptHandler;

  static GameCamera mainCamera;
  static bool menuIsUp;

  void demoShowGui();
  GLfloat calculateDeltaTime();
  void update(GLfloat deltaTime);
  void processInput(GLFWwindow *window, GLfloat deltaTime);

  void demoInitLuaState();
  void demoPassLuaCoreUtils();
  void demoInitLua();
  void demoStartLuaLoop();

public:
  GameHandler();
  ~GameHandler();

  void demoInit();
  void demoMainLoop(const core::Window &window);
  void demoCleanup();

  static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
  static void defaultFramebufferSizeCallback(GLFWwindow *window, int width,
                                             int height);
  static void scrollCallback(GLFWwindow *window, double xoffset,
                             double yoffset);
};

} // namespace testgame

#endif
