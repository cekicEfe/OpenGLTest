#include "GameEntity.hpp"

using namespace testgame;

GameEntity::GameEntity ()
{
}

GameEntity::GameEntity (Model::Model &model, glm::vec3 modelScale,
                        Shader &shader, glm::quat rot, glm::vec3 pos,
                        testgame::HitBox *hitbox, glm::vec3 hitboxscale)
    : core::CoreEntity (model, modelScale, shader, rot, pos)
{
  this->mpHitbox = hitbox;
  this->mHitboxScale = hitboxscale;
}

GameEntity::~GameEntity ()
{
}
