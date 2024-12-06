#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include "CoreClass/CoreEntity/CoreEntity.h"
#include "HitBox/HitBox.h"
#include "glm/fwd.hpp"

namespace testgame
{
class GameEntity : public core::CoreEntity
{
private:
  testgame::HitBox *mpHitbox = nullptr;
  glm::vec3 mHitboxScale = { 1.0f, 1.0f, 1.0f };

public:
  GameEntity ();
  GameEntity (Model::Model &model, glm::vec3 modelScale, Shader &shader,
              glm::quat rot, glm::vec3 pos, testgame::HitBox *hitbox,
              glm::vec3 hitboxscale);
  virtual ~GameEntity ();
};
}

#endif
