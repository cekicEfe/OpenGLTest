#include "GameEntity.hpp"
#include <App/DemoGame/GameScript/GameScript.hpp>
#include <memory>
#include <sol/forward.hpp>
#include <sol/raii.hpp>
#include <stdexcept>

using namespace testgame;

GameEntity::GameEntity ()
{
}

GameEntity::~GameEntity ()
{
}

void
GameEntity::useScript (const std::string &scriptName, sol::state &luaState)
{
}

void
GameEntity::setHitbox (const std::shared_ptr<testgame::GameHitBox> &hitbox)
{
  this->mpHitbox = hitbox;
}

void
GameEntity::setHitboxScale (const glm::vec3 &HBscale)
{
  this->mHitboxScale = HBscale;
}

const testgame::GameHitBox *const
GameEntity::getHitBox () const
{
  if (this->mpHitbox.lock ())
    return this->mpHitbox.lock ().get ();
  else
    return nullptr;
}

const glm::vec3 &
GameEntity::getHitBoxScale () const
{
  return this->mHitboxScale;
}

void
GameEntity::update (GLfloat deltaTime)
{
}
