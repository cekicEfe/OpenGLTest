#include "GameHandler.hpp"
#include "App/DemoGame/GameEntity/GameEntity.hpp"
#include "App/DemoGame/GameLight/GameLight.hpp"
#include "App/DemoGame/GameModel/GameModel.hpp"
#include "App/DemoGame/GameShader/GameShader.hpp"
#include "glfw3.h"
#include "glm/gtc/constants.hpp"
#include <GraphicsBackend/Animation/Animation.hpp>
#include <GraphicsBackend/Animator/Animator.hpp>
#include <assimp/anim.h>
#include <assimp/material.h>
#include <cstddef>
#include <filesystem>
#include <imgui.h>
#include <memory>
#include <sol/state.hpp>
#include <string>

namespace fs = std::filesystem;

// sol::state testgame::GameHandler::scriptHandler;
testgame::GameCamera testgame::GameHandler::mainCamera;
bool testgame::GameHandler::menuIsUp = true;

testgame::GameHandler::GameHandler() {}

testgame::GameHandler::~GameHandler() {}

void testgame::GameHandler::demoInitLuaState() {
  this->scriptHandler.reset();
  this->scriptHandler = std::make_unique<sol::state>();
  this->scriptHandler.get()->open_libraries(sol::lib::base);
}

void testgame::GameHandler::demoPassLuaCoreUtils() {
  // Pass gameEntity
  this->scriptHandler.get()->new_usertype<testgame::GameEntity>("GameEntity");
  (*this->scriptHandler.get())["GameEntity"]["getPos"] =
      [](testgame::GameEntity &self) -> std::vector<float> {
    return {self.getPos().x, self.getPos().y, self.getPos().z};
  };
  (*this->scriptHandler.get())["GameEntity"]["setPos"] =
      [](testgame::GameEntity &self, float x, float y, float z) -> void {
    self.setPos({x, y, z});
  };
}

void testgame::GameHandler::demoInitLua() {
  this->demoInitLuaState();
  this->demoPassLuaCoreUtils();
}

void testgame::GameHandler::demoStartLuaLoop() {}

void testgame::GameHandler::demoInit() { demoInitLua(); }

void testgame::GameHandler::demoShowGui() {
  static ImGui::FileBrowser browser;
  static std::string model_name = "Pick Model";
  static fs::path model_path = "Pick Model";
  static bool picking_model = false;

  static std::string frag_name = "Pick Fragmant shader";
  static fs::path frag_path = "Pick Fragmant shader";
  static bool picking_frag = false;

  static std::string vert_name = "Pick Vertex shader";
  static fs::path vert_path = "Pick Vertex shader";
  static bool picking_vert = false;

  // Helper lambdas to get past repetition
  auto preparePicker = [](ImGui::FileBrowser &browser, const std::string &title,
                          const std::vector<std::string> &filter, bool &cond) {
    browser.SetTitle(title);
    browser.SetTypeFilters(filter);
    cond = true;
    browser.Open();
  };
  auto createPicker = [](ImGui::FileBrowser &browser, std::string &filename,
                         fs::path &path, bool &cond) {
    path = browser.GetSelected();
    filename = browser.GetSelected().filename().string();
    cond = false;
    browser.ClearSelected();
  };

  {
    ImGui::Begin("Create Entity");

    // We select models here
    if (ImGui::CollapsingHeader("Model selector")) {
      ImGui::Indent();
      static bool model_already_exists = false;
      static bool is_first_try = true;
      static bool flip_textures = true;

      ImGui::BulletText("Model : %s", model_name.c_str());
      ImGui::BulletText("Model path : %s", model_path.c_str());

      if (ImGui::Button("Pick Model")) {
        std::string title("Pick Model");
        std::vector<std::string> filter = {".obj", ".fbx", ".dae"};
        preparePicker(browser, title, filter, picking_model);
      }

      if (model_already_exists && !is_first_try) {
        ImGui::BulletText(
            "Selected model is already loaded or not a valid path");
      }

      if (ImGui::Button("Import model")) {
        is_first_try = false;
        if (fs::exists(model_path)) {
          for (size_t i = 0; i < this->models.size(); i++) {
            if (this->models[i].get()->getModelName() == model_name) {
              model_already_exists = true;
              break;
            } else if (this->models[i].get()->getModelName() != model_name &&
                       i == this->models.size() - 1) {
              model_already_exists = false;
            }
          }
          if (!model_already_exists) {
            this->models.push_back(std::make_shared<testgame::GameModel>(
                model_path, model_name, false, flip_textures));
            std::cout << "A model is imported!" << std::endl;
          }
        } else {
          model_already_exists = true;
        }
      }

      ImGui::SameLine();

      ImGui::Checkbox("Import textures flipped ", &flip_textures);

      ImGui::Unindent();
    }

    // We select shaders here
    if (ImGui::CollapsingHeader("Shader selector")) {
      ImGui::Indent();
      static bool shader_already_exists = false;
      static bool is_first_try = true;

      ImGui::BulletText("Vert : %s", vert_name.c_str());
      ImGui::BulletText("Vert path : %s", vert_path.c_str());
      if (ImGui::Button("Pick Vert shader")) {
        std::string title("Pick Vert shader");
        std::vector<std::string> filter = {".vs", ".vert"};
        preparePicker(browser, title, filter, picking_vert);
      }

      ImGui::BulletText("Frag : %s", frag_name.c_str());
      ImGui::BulletText("Frag path : %s", frag_path.c_str());
      if (ImGui::Button("Pick Fragmant shader")) {
        std::string title("Pick Fragmant shader");
        std::vector<std::string> filter = {".fs", ".frag"};
        preparePicker(browser, title, filter, picking_frag);
      }

      if (!is_first_try && shader_already_exists) {
        ImGui::BulletText("Selected Shader already exists or shader "
                          "components are not valid");
      }

      if (ImGui::Button("Create Shader")) {
        std::string shader_name;
        is_first_try = false;
        if (fs::exists(frag_path) && fs::exists(vert_path)) {
          if (frag_name.substr(0, frag_name.find_last_of(".")) ==
              vert_name.substr(0, vert_name.find_last_of("."))) {
            shader_name = frag_name.substr(0, frag_name.find_last_of("."));
            for (size_t i = 0; i < this->shaders.size(); i++) {
              if (this->shaders[i].get()->getShaderName() == shader_name) {
                shader_already_exists = true;
                break;
              } else if (this->shaders[i].get()->getShaderName() !=
                             shader_name &&
                         i == this->shaders.size() - 1) {
                shader_already_exists = false;
              }
            }
          }
          if (!shader_already_exists) {
            try {
              this->shaders.push_back(std::make_shared<testgame::GameShader>(
                  vert_path.c_str(), frag_path.c_str(), shader_name));
              std::cout << "A shader created" << std::endl;
            } catch (...) {
              std::cout << "While creating a shader an error occured"
                        << std::endl;
            }
          }
        } else {
          shader_already_exists = true;
        }
      }
      ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Create Entity")) {
      ImGui::Indent();
      static size_t shader_index = 0;
      static size_t model_index = 0;

      ImGui::BulletText("Select model");
      for (size_t i = 0; i < this->models.size(); i++) {
        ImGui::Indent();
        ImGui::BulletText("Model name : %s",
                          this->models[i].get()->getModelName().c_str());
        ImGui::SameLine();
        std::string select_model =
            "Select : " + this->models[i].get()->getModelName();
        if (ImGui::Button(select_model.c_str())) {
          model_index = i;
        }
        ImGui::Unindent();
      }

      ImGui::BulletText("Select shader");
      for (size_t i = 0; i < this->shaders.size(); i++) {
        ImGui::Indent();
        ImGui::BulletText("Shader name : %s",
                          this->shaders[i].get()->getShaderName().c_str());
        ImGui::SameLine();
        std::string shader_name =
            "Select shader : " + this->shaders[i].get()->getShaderName();
        if (ImGui::Button(shader_name.c_str())) {
          shader_index = i;
        }
        ImGui::Unindent();
      }

      if (ImGui::Button("Create entity")) {
        if (!this->models.empty() && !this->shaders.empty()) {
          this->entities.push_back(std::make_shared<testgame::GameEntity>());
          this->entities[this->entities.size() - 1].get()->setModel(
              this->models[model_index]);
          this->entities[this->entities.size() - 1].get()->setShader(
              this->shaders[shader_index]);
        }
      }

      ImGui::Unindent();
    }

    ImGui::End();

    if (browser.HasSelected() && picking_model) {
      createPicker(browser, model_name, model_path, picking_model);
    }
    if (browser.HasSelected() && picking_frag) {
      createPicker(browser, frag_name, frag_path, picking_frag);
    }
    if (browser.HasSelected() && picking_vert) {
      createPicker(browser, vert_name, vert_path, picking_vert);
    }
  }

  {
    ImGui::Begin("Entities");
    static int selected = -1;
    ImGui::BulletText("Selected entity index : %d", selected);
    if (ImGui::Button("Destroy selected object") && selected != -1 &&
        selected < this->entities.size()) {
      this->entities.erase(this->entities.begin() + selected);
      selected = -1;
    }
    for (size_t i = 0; i < this->entities.size(); i++) {
      std::string title = "Entity " + std::to_string(i + 1);
      if (ImGui::CollapsingHeader(title.c_str())) {
        ImGui::Indent();

        static glm::vec3 pos;
        pos = this->entities[i].get()->getPos();
        std::string x = "x : " + std::to_string(i + 1);
        std::string y = "y : " + std::to_string(i + 1);
        std::string z = "z : " + std::to_string(i + 1);
        ImGui::DragFloat(x.c_str(), &pos.x, 0.5, 10.0f, -10.0f);
        ImGui::DragFloat(y.c_str(), &pos.y, 0.5, 10.0f, -10.0f);
        ImGui::DragFloat(z.c_str(), &pos.z, 0.5, 10.0f, -10.0f);
        this->entities[i].get()->setPos(pos);

        static GLfloat rotation;
        rotation = this->entities[i].get()->getRotRad();
        std::string floater_title = std::to_string(i + 1) + " Rotation";
        ImGui::DragFloat(floater_title.c_str(), &rotation, 0.1,
                         -glm::two_pi<float>(), glm::two_pi<float>());
        this->entities[i].get()->setRotRad(rotation);

        ImGui::Unindent();
      }
      if (ImGui::Button(("Select" + title).c_str())) {
        selected = i;
      }
    }

    ImGui::End();
  }

  browser.Display();
}

void testgame::GameHandler::demoMainLoop(const core::Window &window) {
  float deltaTime = this->calculateDeltaTime();
  this->processInput(window.returnGLFWWindow(), deltaTime);
  this->demoShowGui();
  this->demoStartLuaLoop();
  // static Model::Model animatedModelDemo(
  //     ,
  //     false, false);

  // static Model::Animation animation(
  //     ,
  //     &animatedModelDemo);

  // static Model::Animator animator(&animation);
  // static std::string vertPath();
  // static std::string fragPath(
  //     );
  // static Shader animationShader(vertPath.c_str(), fragPath.c_str());

  // animator.UpdateAnimation(deltaTime);

  // Renders gameHandler owned objects
  // for (size_t i = 0; i < this->entities.size(); i++) {
  //   auto entity_shader = this->entities[i].get()->getShader();
  //   auto entity_model = this->entities[i].get()->getModel();

  //   if (entity_shader != nullptr && entity_model != nullptr) {
  //     entity_shader->use();

  //     glm::mat4 view = this->mainCamera.GetViewMatrix();
  //     glm::mat4 projection =
  //         this->mainCamera.GetProjection(window.GetAspectRatio());
  //     glm::mat4 uniformAlig = this->entities[i].get()->getUniformAlignment();

  //     entity_shader->setMat4("view", view);
  //     entity_shader->setMat4("projection", projection);
  //     entity_shader->setMat4("model", uniformAlig);
  //     entity_model->Draw(*entity_shader);

  //     entity_shader->stop();
  //   }
  // }

  // render demo animated object
  // animationShader.use();
  // glm::mat4 projection =
  //     this->mainCamera.GetProjection(window.GetAspectRatio());
  // glm::mat4 view = this->mainCamera.GetViewMatrix();
  // animationShader.setMat4("projection", projection);
  // animationShader.setMat4("view", view);

  // auto transforms = animator.GetFinalBoneMatrices();
  // for (int i = 0; i < transforms.size(); ++i)
  //   animationShader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]",
  //                           transforms[i]);
  // glm::mat4 model = glm::mat4(1.0f);
  // model = glm::translate(
  //     model,
  //     glm::vec3(0.0f, -0.4f,
  //               0.0f)); // translate it down so it's at the center of the
  //               scene
  // model = glm::scale(
  //     model,
  //     glm::vec3(.5f, .5f,
  //               .5f)); // it's a bit too big for our scene, so scale it down
  // animationShader.setMat4("model", model);
  // animatedModelDemo.Draw(animationShader);
  // animationShader.stop();
}

void testgame::GameHandler::demoCleanup() {}

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

void testgame::GameHandler::update(GLfloat deltaTime) {}

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
}

void testgame::GameHandler::mouse_callback(GLFWwindow *window, double xposIn,
                                           double yposIn) {
  static bool first_camera = testgame::GameHandler::menuIsUp;
  static double lastX = 0;
  static double lastY = 0;

  float ypos = static_cast<float>(yposIn);
  float xpos = static_cast<float>(xposIn);

  float xoffset = 0;
  float yoffset = 0;

  if (testgame::GameHandler::menuIsUp) {
    first_camera = true;
  }
  if (!testgame::GameHandler::menuIsUp) {
    if (first_camera) {
      lastX = xpos;
      lastY = ypos;
      first_camera = false;
    } else {
      xoffset = xpos - lastX;
      yoffset = lastY - ypos; // reversed since y-coordinates go
                              // from bottom to top
      lastX = xpos;
      lastY = ypos;
    }
    mainCamera.ProcessMouseMovement(xoffset, yoffset);
  }
};

void testgame::GameHandler::defaultFramebufferSizeCallback(GLFWwindow *window,
                                                           int width,
                                                           int height) {
  glViewport(0, 0, width, height);
};

void testgame::GameHandler::scrollCallback(GLFWwindow *window, double xoffset,
                                           double yoffset) {
  if (!testgame::GameHandler::menuIsUp)
    mainCamera.ProcessMouseScroll(static_cast<float>(yoffset));
};
