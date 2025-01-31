#include "GameEntity.hpp"

using namespace testgame;

GameEntity::GameEntity ()
{
}

GameEntity::GameEntity (Model::Model &model, glm::vec3 modelScale,
                        Shader &shader, glm::vec3 rotaxis, GLfloat rotrad,
                        glm::vec3 pos, testgame::HitBox *hitbox,
                        glm::vec3 hitboxscale)
    : core::CoreEntity (model, modelScale, shader, rotaxis, rotrad, pos)
{
  this->mpHitbox = hitbox;
  this->mHitboxScale = hitboxscale;
}

GameEntity::~GameEntity ()
{
}

void
GameEntity::update (GLfloat deltaTime)
{
}
