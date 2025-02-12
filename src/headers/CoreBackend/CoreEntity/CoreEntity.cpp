#include "CoreEntity.h"

core::CoreEntity::CoreEntity() {}

core::CoreEntity::CoreEntity(const std::shared_ptr<Model::Model> &model,
                             const std::shared_ptr<Shader> &shader,
                             glm::vec3 modelScale, glm::vec3 pos, glm::vec3 rot,
                             GLfloat rotrad) {
  this->mpModel = model;
  this->mModelScale = modelScale;
  this->mpShader = shader;
  this->mPos = pos;
  this->mRotAxis = rot;
  this->mRotDegreeRad = rotrad;
}

core::CoreEntity::~CoreEntity() {}

const Model::Model *const core::CoreEntity::getModel() const {
  return this->mpModel.lock().get();
}

const Shader *const core::CoreEntity::getShader() const {
  return this->mpShader.lock().get();
}

const glm::vec3 &core::CoreEntity::getModelScale() const {
  return this->mModelScale;
}

const glm::vec3 &core::CoreEntity::getPos() const { return this->mPos; }

const glm::vec3 &core::CoreEntity::getRotAxis() const { return this->mRotAxis; }

const GLfloat &core::CoreEntity::getRotRad() const {
  return this->mRotDegreeRad;
}

void core::CoreEntity::setShader(const std::shared_ptr<Shader> &shader) {
  this->mpShader = shader;
}

void core::CoreEntity::setModel(const std::shared_ptr<Model::Model> modelptr) {
  this->mpModel = modelptr;
}

void core::CoreEntity::setModelScale(const glm::vec3 &modelScale) {
  this->mModelScale = modelScale;
}

void core::CoreEntity::setPos(const glm::vec3 &mvcomp) { this->mPos = mvcomp; }

void core::CoreEntity::setRotAxis(const glm::vec3 &rtaxis) {
  this->mRotAxis = rtaxis;
}

void core::CoreEntity::setRotRad(const GLfloat &rotRad) {
  this->mRotDegreeRad = rotRad;
}

const glm::mat4 core::CoreEntity::getUniformAlignment() const {
  glm::mat4 modelMatrix = glm::mat4(1.0);
  modelMatrix = glm::translate(modelMatrix, this->mPos);
  modelMatrix = glm::scale(modelMatrix, this->mModelScale);
  modelMatrix = glm::rotate(modelMatrix, this->mRotDegreeRad, this->mRotAxis);
  return modelMatrix;
}
//
