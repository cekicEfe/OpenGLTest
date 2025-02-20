#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "App/DemoGame/GameHitBox/GameHitBox.hpp"
#include "CoreBackend/CoreEntity/CoreEntity.h"
#include "GraphicsBackend/Model/Model.h"
#include "glm/fwd.hpp"
#include <memory>

namespace testgame {
class GameEntity : public core::CoreEntity {
private:
  std::weak_ptr<testgame::GameHitBox> mpHitbox;
  glm::vec3 mHitboxScale = {1.0f, 1.0f, 1.0f};

  // glm::vec3 mSpeedVec = {0.0f, 0.0f, 0.0f};
  // glm::vec3 mAccVec = {0.0f, 0.0f, 0.0f};

  // GLfloat mRotSpeed = 0;
  // GLfloat mRotAcc = 0;

public:
  GameEntity();
  GameEntity(const std::shared_ptr<Model::Model> &model,
             const std::shared_ptr<Shader> &shader,
             const std::shared_ptr<testgame::GameHitBox> hitbox,
             glm::vec3 hitboxscale, glm::vec3 modelScale, glm::vec3 pos,
             glm::vec3 rotaxis, GLfloat rotrad);
  virtual ~GameEntity();

  void setHitbox(const std::shared_ptr<testgame::GameHitBox> &hitbox);
  void setHitboxScale(const glm::vec3 &HBscale);
  // void setSpeedVec(const glm::vec3 &speedVec);
  // void setAccVec(const glm::vec3 &accVec);
  // void setRotSpeed(const GLfloat &rotSpeed);
  // void setRotAcc(const GLfloat &rocAcc);

  const testgame::GameHitBox *const getHitBox() const;
  const glm::vec3 &getHitBoxScale() const;
  // const glm::vec3 &getSpeedVec() const;
  // const glm::vec3 &getAccVec() const;
  // const GLfloat &getRotSpeed() const;
  // const GLfloat &getRotAcc() const;

  virtual void update(GLfloat deltaTime);
};
} // namespace testgame

#endif
