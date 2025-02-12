#include "GameEntity.hpp"

using namespace testgame;

GameEntity::GameEntity() {}

GameEntity::GameEntity(const std::shared_ptr<Model::Model> &model,
                       const std::shared_ptr<Shader> &shader,
                       const std::shared_ptr<testgame::GameHitBox> hitbox,
                       glm::vec3 hitboxscale, glm::vec3 modelScale,
                       glm::vec3 pos, glm::vec3 rotaxis, GLfloat rotrad)
    : core::CoreEntity(model, shader, modelScale, pos, rotaxis, rotrad) {
  this->mpHitbox = hitbox;
  this->mHitboxScale = hitboxscale;
}

GameEntity::~GameEntity() {}

void GameEntity::setHitbox(
    const std::shared_ptr<testgame::GameHitBox> &hitbox) {
  this->mpHitbox = hitbox;
}
void GameEntity::setHitboxScale(const glm::vec3 &HBscale) {
  this->mHitboxScale = HBscale;
}
void GameEntity::setSpeedVec(const glm::vec3 &speedVec) {
  this->mSpeedVec = speedVec;
}
void GameEntity::setAccVec(const glm::vec3 &accVec) {
  //
  this->mAccVec = accVec;
}
void GameEntity::setRotSpeed(const GLfloat &rotSpeed) {
  this->mRotSpeed = rotSpeed;
}
void GameEntity::setRotAcc(const GLfloat &rocAcc) { this->mRotAcc = rocAcc; }

const testgame::GameHitBox *const GameEntity::getHitBox() const {
  return this->mpHitbox.lock().get();
}
const glm::vec3 &GameEntity::getHitBoxScale() const {
  return this->mHitboxScale;
}
const glm::vec3 &GameEntity::getSpeedVec() const { return this->mSpeedVec; }
const glm::vec3 &GameEntity::getAccVec() const { return this->mAccVec; }
const GLfloat &GameEntity::getRotSpeed() const { return this->mRotSpeed; }
const GLfloat &GameEntity::getRotAcc() const { return this->mRotAcc; }

void GameEntity::update(GLfloat deltaTime) {}
