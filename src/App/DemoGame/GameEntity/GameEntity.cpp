#include "GameEntity.hpp"

using namespace testgame;

GameEntity::GameEntity() {}

GameEntity::GameEntity(
    const std::shared_ptr<Model::Model> &model,
    const std::shared_ptr<Shader> &shader,
    const std::shared_ptr<testgame::GameHitBox> &hitbox,
    const std::map<std::string, std::shared_ptr<std::string>> &scripts,
    const glm::vec3 &hitboxscale, const glm::vec3 &modelScale,
    const glm::vec3 &pos, const glm::vec3 &rotaxis, const GLfloat &rotrad)
    : core::CoreEntity(model, shader, modelScale, pos, rotaxis, rotrad) {
  this->mpHitbox = hitbox;
  this->mHitboxScale = hitboxscale;
  for (auto &elem : scripts) {
    this->scripts.insert({elem.first, elem.second});
  }
}

GameEntity::~GameEntity() {}

void GameEntity::setHitbox(
    const std::shared_ptr<testgame::GameHitBox> &hitbox) {
  this->mpHitbox = hitbox;
}

void GameEntity::setHitboxScale(const glm::vec3 &HBscale) {
  this->mHitboxScale = HBscale;
}

const testgame::GameHitBox *const GameEntity::getHitBox() const {
  if (this->mpHitbox.lock())
    return this->mpHitbox.lock().get();
  else
    return nullptr;
}

const glm::vec3 &GameEntity::getHitBoxScale() const {
  return this->mHitboxScale;
}

void GameEntity::update(GLfloat deltaTime) {}
