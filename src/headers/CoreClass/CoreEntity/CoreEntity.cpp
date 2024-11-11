#include "CoreEntity.h"
#include "CoreClass/MathConstants/MathContstants.hpp"

core::CoreEntity::CoreEntity ()
{
}

core::CoreEntity::CoreEntity (Model::Model &model, glm::vec3 modelScale,
                              core::HitBox &hitbox, glm::vec3 hitboxScale,
                              Shader &shader, core::MovementComponent mvcomp,
                              core::RotationComponent rtcomp)
{
  this->mpModel = &model;
  this->mModelScale = modelScale;
  this->mpHitbox = &hitbox;
  this->mHitboxScale = hitboxScale;
  this->mpShader = &shader;
  this->mMovComponent = mvcomp;
  this->mRotComponent = rtcomp;
}

core::CoreEntity::~CoreEntity ()
{
}

void
core::CoreEntity::update (GLfloat deltaTime)
{
  this->mMovComponent.speed += this->mMovComponent.acc * deltaTime;
  this->mMovComponent.pos += this->mMovComponent.speed * deltaTime;
  this->mMovComponent.acc = { 0.0f, 0.0f, 0.0f };
}

const Shader *const
core::CoreEntity::getShader () const
{
  return this->mpShader;
}

const Model::Model *const
core::CoreEntity::getModel () const
{
  return this->mpModel;
}

const glm::vec3 *const
core::CoreEntity::getModelScale () const
{
  return &this->mModelScale;
}

const core::HitBox *const
core::CoreEntity::getHitbox () const
{
  return this->mpHitbox;
}

const glm::vec3 *const
core::CoreEntity::getHitboxScale () const
{
  return &this->mHitboxScale;
}

const core::MovementComponent *const
core::CoreEntity::getMovementComp () const
{
  return &this->mMovComponent;
}

const core::RotationComponent *const
core::CoreEntity::getRotationComp () const
{
  return &this->mRotComponent;
}

void
core::CoreEntity::setShader (Shader *const shader)
{
  this->mpShader = shader;
}

void
core::CoreEntity::setModel (Model::Model *const modelptr)
{
  this->mpModel = modelptr;
}

void
core::CoreEntity::setModelScale (const glm::vec3 &modelScale)
{
  this->mModelScale = modelScale;
}

void
core::CoreEntity::setHitbox (core::HitBox *const hitboxptr)
{
  this->mpHitbox = hitboxptr;
}

void
core::CoreEntity::setHitboxScale (const glm::vec3 &hitboxscale)
{
  this->mHitboxScale = hitboxscale;
}

void
core::CoreEntity::setMovementComp (const core::MovementComponent &mvcomp)
{
  this->mMovComponent = mvcomp;
}

void
core::CoreEntity::setRotationComp (const core::RotationComponent &rtcomp)
{
  this->mRotComponent = rtcomp;
}

//
