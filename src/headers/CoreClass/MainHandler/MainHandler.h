#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <memory>
#include <model/Camera.h>
#include <model/Model.h>
#include <model/Shaders.h>

#include <CoreClass/CoreClassPreDec.h>
#include <CoreClass/CoreEntity/CoreEntity.h>
#include <CoreClass/HitBox/CollisionDetector/OctTree/OctTree.hpp>
#include <CoreClass/JsonExtractor/JsonExtractor.h>
#include <CoreClass/RenderHandler/RenderHandler.h>
#include <CoreClass/SaveLoadHandler/SaveLoadHandler.h>

#include "MyPaths.h"
#include <filesystem>
#include <imgui/imgui.h>
#include <json/json.hpp>
#include <unordered_map>
#include <vector>

namespace core {

class MainHandlerVariables {
private:
  const GLuint SCR_WIDTH = 1920;
  const GLuint SCR_HEIGHT = 1080;
  Camera mainCamera;
  GLfloat lastX = SCR_WIDTH / 2.0f;
  GLfloat lastY = SCR_HEIGHT / 2.0f;
  GLboolean firstMouse = true;
  GLuint counter = 0;
  GLboolean simuFlag = false;
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  friend class MainHandler;
} static MainHandlerVariables;

class MainHandler {
private:
  static std::unordered_map<
      std::string, std::pair<std::unique_ptr<Model::Model>,
                             std::vector<std::shared_ptr<core::CoreEntity>>>>
      msEntityBatch;

  static std::vector<std::string> msShaderPaths;
  static std::vector<std::string> msJsonPreceptPaths;
  static std::vector<std::string> msJsonScenePaths;

  static std::vector<std::unique_ptr<nlohmann::json>> msJsonScenes;
  static std::vector<std::unique_ptr<nlohmann::json>> msJsonPrecepts;
  static std::vector<std::unique_ptr<Model::Light>> msLights;
  static std::vector<std::unique_ptr<Shader>> msShaders;

  static void addCoreEntity();
  static void addCoreEntity(Model::Model *entityModel);

public:
  MainHandler();
  ~MainHandler();

  static void coreDemo();
  static void mouse_callback(GLFWwindow *window, double xpos, double ypos);
  static void scroll_callback(GLFWwindow *window, double xoffset,
                              double yoffset);
  static void framebuffer_size_callback(GLFWwindow *window, int width,
                                        int height);
  static void processInput(GLFWwindow *window, GLfloat deltaTime);

  static void DrawInstanced();
  static void DrawInstancedWithInterval(GLfloat deltaTime, GLfloat intervalMS);

  static void showGui();

  static void calculateDeltaTime();
  static GLfloat returnDeltaTime();

  static GLuint returnSCR_WIDTH();
  static GLuint returnSCR_HEIGHT();
};

} // namespace core

#endif
