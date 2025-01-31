#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "CoreBackend/CoreEntity/CoreEntity.h"
#include "HitBox/HitBox.h"
#include "glm/fwd.hpp"

namespace testgame {
class GameEntity : public core::CoreEntity {
private:
  testgame::HitBox *mpHitbox = nullptr;
  glm::vec3 mHitboxScale = {1.0f, 1.0f, 1.0f};

  glm::vec3 mSpeedVec = {0.0f, 0.0f, 0.0f};
  glm::vec3 mAccVec = {0.0f, 0.0f, 0.0f};

  GLfloat mRotSpeed = 0;
  GLfloat mRotAcc = 0;

public:
  GameEntity();
  GameEntity(Model::Model &model, glm::vec3 modelScale, Shader &shader,
             glm::vec3 rotaxis, GLfloat rotrad, glm::vec3 pos,
             testgame::HitBox *hitbox, glm::vec3 hitboxscale);
  virtual ~GameEntity();
  virtual void update(GLfloat deltaTime);
};
} // namespace testgame

#endif
