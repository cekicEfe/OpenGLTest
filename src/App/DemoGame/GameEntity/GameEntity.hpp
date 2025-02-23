#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "App/DemoGame/GameHitBox/GameHitBox.hpp"
#include "CoreBackend/CoreEntity/CoreEntity.h"
#include "GraphicsBackend/Model/Model.h"
#include "glm/fwd.hpp"
#include <map>
#include <memory>
#include <sol/forward.hpp>
#include <string>

namespace testgame {
class GameEntity : public core::CoreEntity {
private:
  std::weak_ptr<testgame::GameHitBox> mpHitbox;
  glm::vec3 mHitboxScale = {1.0f, 1.0f, 1.0f};
  // script name / script itself
  std::map<std::string, std::weak_ptr<std::string>> scripts;

public:
  std::unique_ptr<sol::table> externalTable;

  GameEntity();
  GameEntity(const std::shared_ptr<Model::Model> &model,
             const std::shared_ptr<Shader> &shader,
             const std::shared_ptr<testgame::GameHitBox> &hitbox,
             const std::map<std::string, std::shared_ptr<std::string>> &scripts,
             const glm::vec3 &hitboxscale, const glm::vec3 &modelScale,
             const glm::vec3 &pos, const glm::vec3 &rotaxis,
             const GLfloat &rotrad);
  virtual ~GameEntity();

  void setHitbox(const std::shared_ptr<testgame::GameHitBox> &hitbox);
  const testgame::GameHitBox *const getHitBox() const;

  void setHitboxScale(const glm::vec3 &HBscale);
  const glm::vec3 &getHitBoxScale() const;

  virtual void update(GLfloat deltaTime);
};
} // namespace testgame

#endif
