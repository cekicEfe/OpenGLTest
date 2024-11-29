#include "CoreEntity.h"

core::CoreEntity::CoreEntity ()
{
}

core::CoreEntity::CoreEntity (Model::Model &model, glm::vec3 modelScale,
                              core::HitBox &hitbox, glm::vec3 hitboxScale,
                              Shader &shader, glm::quat rtcomp,
                              glm::vec3 mvcomp)
{
  this->mpModel = &model;
  this->mModelScale = modelScale;
  this->mpHitbox = &hitbox;
  this->mHitboxScale = hitboxScale;
  this->mpShader = &shader;
  this->mPos = mvcomp;
  this->mQuatRot = rtcomp;
}

core::CoreEntity::~CoreEntity ()
{
}

void
core::CoreEntity::update (GLfloat deltaTime)
{
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

const glm::vec3 *const
core::CoreEntity::getPos () const
{
  return &this->mPos;
}

const glm::quat *const
core::CoreEntity::getRot () const
{
  return &this->mQuatRot;
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
core::CoreEntity::setPos (const glm::vec3 &mvcomp)
{
  this->mPos = mvcomp;
}

void
core::CoreEntity::setRot (const glm::quat &rtcomp)
{
  this->mQuatRot = rtcomp;
}

//
